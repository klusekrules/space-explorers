#include "Kompresja.h"
#include "zlib.h"
#include <assert.h>
#include <WinSock2.h>
#include "RPC\StaleRPC.h"

#define CHUNK 262144

SpEx::Kompresja::Kompresja(FILE * in, FILE* out)
	: plikin_(in),plikout_(out), danein_(nullptr), daneout_(nullptr)
{
}

SpEx::Kompresja::Kompresja(const std::string & in, std::string & out)
	: danein_(&in), daneout_(&out), plikin_(nullptr), plikout_(nullptr)
{
}

SpEx::Kompresja::~Kompresja(){
}

int SpEx::Kompresja::kompresja(){
	if (plikin_ != nullptr && plikout_ != nullptr)
		return kompresja_file_impl();
	if (danein_ != nullptr && daneout_ != nullptr)
		return kompresja_mem_impl();
	return ERROR_UNIDENTIFYING_COMPRESION_DATA_SOURCE;
}

int SpEx::Kompresja::kompresja_mem_impl(){
	auto rozmiar = danein_->size();
	auto bound = compressBound(rozmiar);
	uLongf after = bound;
	std::string out;
	out.resize(after, 0);
	switch (compress((Bytef*)out.data(), &after, (const Bytef*)danein_->data(), rozmiar))
	{
	case Z_OK:
	{
		std::string temp;
		temp.push_back((rozmiar >> 24) & 0xff);
		temp.push_back((rozmiar >> 16) & 0xff);
		temp.push_back((rozmiar >> 8) & 0xff);
		temp.push_back(rozmiar & 0xff);
		(*daneout_) = std::move(temp + out);
	}
	break;
	case Z_MEM_ERROR:
		return ERROR_COMPRESION_Z_MEM_ERROR;
		break;
	case Z_BUF_ERROR:
		return ERROR_COMPRESION_Z_BUF_ERROR;
		break;
	default:
		return ERROR_UNIDENTIFYING;
		break;
	}
	return ERROR_SUCCESS;
}

int SpEx::Kompresja::kompresja_file_impl(){
	int level = Z_DEFAULT_COMPRESSION;// The compression level must be Z_DEFAULT_COMPRESSION, or between 0 and 9: 1 gives best speed, 9 gives best compression, 0 gives no compression at all (the input data is simply copied a block at a time). Z_DEFAULT_COMPRESSION requests a default compromise between speed and compression (currently equivalent to level 6). 
	int ret, flush;
	unsigned have;
	z_stream strm;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];
	
	/* allocate deflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	ret = deflateInit(&strm, level);
	if (ret != Z_OK)
		return ret;

	/* compress until end of file */
	do {

		strm.avail_in = fread(in, 1, CHUNK, plikin_);
		if (ferror(plikin_)) {
			(void)deflateEnd(&strm);
			return Z_ERRNO;
		}
		flush = feof(plikin_) ? Z_FINISH : Z_NO_FLUSH;
		strm.next_in = in;
		/* run deflate() on input until output buffer not full, finish
		compression if all of source has been read in */
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;

			ret = deflate(&strm, flush);    /* no bad return value */
			assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
			have = CHUNK - strm.avail_out;
			if (fwrite(out, 1, have, plikout_) != have || ferror(plikout_)) {
				(void)deflateEnd(&strm);
				return Z_ERRNO;
			}
		} while (strm.avail_out == 0);
		assert(strm.avail_in == 0);     /* all input will be used */
										/* done when last data in file processed */
	} while (flush != Z_FINISH);
	assert(ret == Z_STREAM_END);        /* stream will be complete */
										/* clean up and return */
	(void)deflateEnd(&strm);
	return Z_OK;
}

int SpEx::Kompresja::dekompresja(){
	if (plikin_ != nullptr && plikout_ != nullptr)
		return dekompresja_file_impl();
	if (danein_ != nullptr && daneout_ != nullptr)
		return dekompresja_mem_impl();
	return ERROR_UNIDENTIFYING_DECOMPRESION_DATA_SOURCE;
}

int SpEx::Kompresja::dekompresja_mem_impl(){
	uLongf unSize = danein_->size() - 4;
	uLongf rozmiar = ((u_char)(*danein_)[0] << 24) | ((u_char)(*danein_)[1] << 16) | ((u_char)(*danein_)[2] << 8) | (u_char)(*danein_)[3];
	daneout_->resize(rozmiar, 0);
	return uncompress((Bytef*)daneout_->data(), &rozmiar, (Bytef*)&danein_->data()[4], unSize);
}

int SpEx::Kompresja::dekompresja_file_impl(){
	int ret;
	unsigned have;
	z_stream strm;
	unsigned char in[CHUNK];
	unsigned char out[CHUNK];

	/* allocate inflate state */
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	strm.avail_in = 0;
	strm.next_in = Z_NULL;
	ret = inflateInit(&strm);
	if (ret != Z_OK)
		return ret;

	/* decompress until deflate stream ends or end of file */
	do {
		strm.avail_in = fread(in, 1, CHUNK, plikin_);
		if (ferror(plikin_)) {
			(void)inflateEnd(&strm);
			return Z_ERRNO;
		}
		if (strm.avail_in == 0)
			break;
		strm.next_in = in;

		/* run inflate() on input until output buffer not full */
		do {
			strm.avail_out = CHUNK;
			strm.next_out = out;
			ret = inflate(&strm, Z_NO_FLUSH);
			assert(ret != Z_STREAM_ERROR);  /* state not clobbered */
			switch (ret) {
			case Z_NEED_DICT:
				ret = Z_DATA_ERROR;     /* and fall through */
			case Z_DATA_ERROR:
			case Z_MEM_ERROR:
				(void)inflateEnd(&strm);
				return ret;
			}
			have = CHUNK - strm.avail_out;
			if (fwrite(out, 1, have, plikout_) != have || ferror(plikout_)) {
				(void)inflateEnd(&strm);
				return Z_ERRNO;
			}
		} while (strm.avail_out == 0);

		/* done when inflate() says it's done */
	} while (ret != Z_STREAM_END);

	/* clean up and return */
	(void)inflateEnd(&strm);
	return ret == Z_STREAM_END ? Z_OK : Z_DATA_ERROR;
}



/*switch (ret)
{
case Z_OK:
{
error_ = RPC_OK;
std::string temp;
temp.push_back((rozmiar >> 24) & 0xff);
temp.push_back((rozmiar >> 16) & 0xff);
temp.push_back((rozmiar >> 8) & 0xff);
temp.push_back(rozmiar & 0xff);
out.resize(after);
wyslij_ = temp + out;
}
break;
case Z_MEM_ERROR:
error_ = RPC_ERROR_COMPRESION_Z_MEM_ERROR;
if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)) {
SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Z_MEM_ERROR");
}
break;
case Z_BUF_ERROR:
error_ = RPC_ERROR_COMPRESION_Z_BUF_ERROR;
if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)) {
SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Z_BUF_ERROR");
}
break;
default:
error_ = RPC_ERROR_UNIDENTIFYING;
if (SLog::Log::pobierzInstancje().czyLogiOdblokowane(SLog::Log::Error)) {
SLog::Log::pobierzInstancje().loguj(SLog::Log::Error, "B³¹d kompresji danych: Niezidentyfikowany.");
}
break;
}
return error_;*/

