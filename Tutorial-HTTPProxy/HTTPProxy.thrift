namespace cpp HTTP_Proxy

struct HTTPProxy
{
	1:binary document,
	2:i32 result_code
}

service HttpProxy
{
	HTTPProxy get(1:string URL)
}
