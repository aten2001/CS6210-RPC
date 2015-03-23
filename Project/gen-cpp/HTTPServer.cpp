// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "get_Url.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include <thrift/server/TSimpleServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <queue>
#include <vector>
#include <cstring>
#include <curl/curl.h>


using namespace ::apache::thrift;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;

using boost::shared_ptr;

using namespace  ::HTTP_Server;
using namespace std;


struct Priority_Queue
{
	string URL;
	int32_t size;
};

class queue_Func {
	public:
	    bool operator()(Priority_Queue &q1, Priority_Queue &q2)
	    {
	       return (q1.size < q2.size);
	    }
};
struct wd_in {
  size_t size;
  size_t len;
  char *data;
};


double Cache_Size;
class get_UrlHandler : virtual public get_UrlIf
{
	
	public:
		HTTPServer URLMap;

		map<int32_t,string> URL;
		int32_t index;
		int32_t Cache_Hit;
		int32_t run_policy;
		priority_queue < Priority_Queue, vector<Priority_Queue>, queue_Func> lsf_queue;
	
		get_UrlHandler()
		{
	    		// Your initialization goes here
			cout<<"Cache Size has been set to: "<<Cache_Size<<"\n";
			index=0;
			Cache_Hit=0;
	  	}
		int32_t get_MapSize()
		{
			int32_t tot_size=0;
			std::map<string,string>::iterator i;
			for (i=URLMap.url_Body.begin(); i!=URLMap.url_Body.end(); ++i)
			{
  			tot_size += i->second.size();
  			}
			//cout<<"Total Size of Map: "<<tot_size<<"\n";
  			return tot_size;  
		}
		void remove_fromCache(double remove_Size)
		{
			double free_Size=Cache_Size-get_MapSize();
			if(run_policy==1)
			{
				while(remove_Size>free_Size)
				{
				  	int32_t start;
				  	std::map<int32_t, string>::iterator i = URL.begin();
					start = i->first;  		
					i = URL.find(start);
					string rem_URL = URL[start];
				  	URL.erase(start);
				  	URLMap.url_Body.erase(rem_URL);
				  	cout<<"URL to be removed is : "<<rem_URL<<"\n";
					free_Size=Cache_Size-get_MapSize();
				}
				
			}
			if(run_policy==2)
			{
				while(remove_Size>free_Size)
				{
					  	int32_t start, end, randNum;
					  	std::map<int32_t, string>::iterator i = URL.begin();
					  	start = i->first;
					  	end = index;
					  	while(1)
						{
					  		srand(time(NULL));
					  		randNum = rand() % end + start; 
					  		i = URL.find(randNum);
					  		if(i != URL.end())
							{
					  			break;
							}
					  	}
					  	string rem_URL = URL[randNum];
					  	URL.erase(randNum);
					  	URLMap.url_Body.erase(rem_URL);
					  	cout<<"URL to be removed is : "<<rem_URL<<"\n";
						free_Size=Cache_Size-get_MapSize();
				}

			}
			if(run_policy==3)
			{
				while(remove_Size>free_Size)
				{
					Priority_Queue node = lsf_queue.top();
				 	cout<<"URL to be removed is : "<<node.URL<<"\n";
					URLMap.url_Body.erase(node.URL);
				  	lsf_queue.pop();
					free_Size=Cache_Size-get_MapSize();
				}

			}
		}
		static size_t write_data(void *buffer, size_t size, size_t nmemb, void *userp)
		{
			struct wd_in *wdi = userp;
		  	while(wdi->len + (size * nmemb) >= wdi->size)
			{
				/* check for realloc failing in real code. */
			    	wdi->data = realloc(wdi->data, wdi->size*2);
			    	wdi->size*=2;
		  	}
			memcpy(wdi->data + wdi->len, buffer, size * nmemb);
			wdi->len+=size*nmemb;
			return size * nmemb;
		}
		void get(std::string& _return, const std::string& url, const int32_t policy)
		{
			// Your implementation goes here
			CURL *curl;
			CURLcode res;
			struct wd_in wdi;
			memset(&wdi, 0, sizeof(wdi));
			cout<<"\n\n\nRequested URL: "<<url<<"\n";
			run_policy=policy;
			map<string,string>::iterator i;
			i= URLMap.url_Body.find(url);
			if(i == URLMap.url_Body.end())
			{
				cout<<"No entry found in Map. Cache Miss\n";
				curl = curl_easy_init();

  				if(NULL != curl)			//Fetch page from URL.
				{
					wdi.size = 1024;
					/* Check for malloc failure in real code. */
					wdi.data = malloc(wdi.size);

					/* Set the URL for the operation. */
					curl_easy_setopt(curl, CURLOPT_URL, url.c_str());

					/* "write_data" function to call with returned data. */
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);

					/* userp parameter passed to write_data. */
					curl_easy_setopt(curl, CURLOPT_WRITEDATA, &wdi);

					/* Actually perform the query. */
					res = curl_easy_perform(curl);

				}
				else
				{
					fprintf(stderr, "Error: could not get CURL handle.\n");
				    	exit(EXIT_FAILURE);
				}


				if(wdi.size>Cache_Size)			// If page size is greater than the Cache Size.
				{
					cout<<"Page Size is greater than Cache Size\n";
				}
				else					
				{
					double tot_size = (get_MapSize() + wdi.size);
					if(tot_size> Cache_Size)			//No Space in Cache. Replacement needed.
					{
						cout<<"Cache Limit exceeded. Replacement needs to be done.\n";
						remove_fromCache(wdi.size);
						URLMap.url_Body[url]= wdi.data;
						if(policy ==1 || policy==2) //FIFO or Random
						{
							if(policy==1)
							{
								cout<<"Cache Policy: FIFO Eviction.\n";
							}
							else
							{
								cout<<"Cache Policy: Random Eviction.\n";
							}
							URL[index++]= url;
						}
						else if(policy==3)	//Largest Size
						{
							cout<<"Cache Policy: Largest Size First Eviction.\n";
							Priority_Queue node;
							node.URL= url;
							string body = URLMap.url_Body[url];
							node.size= body.size();
							cout<<"URL: "<<url<<" has size: "<<node.size<<"\n";
							lsf_queue.push(node);
							cout<<"URL inserted in the Cache\n";
						}
					}
					else			//Space available in Cache.
					{
						cout<<"Space available in Cache. No replacement required.\n";
						URLMap.url_Body[url]= wdi.data;
						if(policy==1 || policy==2)
						{
							URL[index++]=url;
							cout<<"Inserted into Map\n";
						}
						else if(policy==3)
						{
							Priority_Queue node;
							node.URL= url;
							string body = URLMap.url_Body[url];
							node.size= body.size();
							cout<<"URL: "<<url<<" has size: "<<node.size<<"\n";
							lsf_queue.push(node);
							cout<<"URL inserted in the Cache\n";	
						}
					}
				}
				_return= wdi.data;
				/* Clean up after ourselves. */
				curl_easy_cleanup(curl);
				/* Now wdi.data has the data from the GET and wdi.len is the length of the data available, so do whatever. */
				/* Write the content to stdout. */
				//write(STDOUT_FILENO, wdi.data, wdi.len);
				/* cleanup wdi.data buffer. */
				free(wdi.data);			    

			}
			else
			{
				Cache_Hit++;	
				cout<<"Entry found in Cache. Cache Hit\n";
				cout << "Cache Hits: " <<Cache_Hit <<"\n";
				_return= URLMap.url_Body[url];
			}
			cout << "Cache Elements: " << URLMap.url_Body.size() << "\n";
			cout << "Size of Cache: " << get_MapSize() << "\n";
		}

};

int main(int argc, char **argv)
{
	// Check the number of parameters
    	if (argc < 2)
	{
		// Tell the user how to run the program
		cerr << "Usage: " << argv[0] << " Cache_Size" << endl;
		/* "Usage messages" are a conventional way of telling the user
		 * how to run a program if they enter the command incorrectly.
		 */
		return 1;
    	}
	Cache_Size=atof(argv[1]);
	int port = 9090;
	shared_ptr<get_UrlHandler> handler(new get_UrlHandler());
	shared_ptr<TProcessor> processor(new get_UrlProcessor(handler));
	shared_ptr<TServerTransport> serverTransport(new TServerSocket(port));
	shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
	shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

	TSimpleServer server(processor, serverTransport, transportFactory, protocolFactory);
	server.serve();
	return 0;
}

