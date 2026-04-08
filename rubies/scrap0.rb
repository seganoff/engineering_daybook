require 'faraday'

cookie_str ="";
cookie_str+='PHPSESSID=ff9d0ce685cbb8ebd381f200acbb1315; ';
cookie_str+='_ga_[...]=GS2.1.[...]; '
#Upgrade-Insecure-Requests: 1
#Sec-Fetch-Dest: document
#Sec-Fetch-Mode: navigate
#Sec-Fetch-Site: none
#Sec-Fetch-User: ?1
#Priority: u=0, i
req_hdr ={'User-Agent'=> #'bukLau'};
"Mozilla/5.0 (Linux; Android 16 Beta 2; Z832 Build/MMB29M) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/134.0.6998.35/36 Mobile Safari/537.36"};
req_hdr.store('Cookie', cookie_str);

from_to = [12606..20794];
width=50;
from=20794;#last+range+1
to  =20794;#from+width;
(from..to).each {|i|
pp "processing #{i}";
lnk = "https://members.___.net/gallery.php?id=#{i}&page=1";
conn=Faraday.new(lnk,params:nil,headers:req_hdr);
resp1=conn.get();
#content_body = resp1.body;
File.write("links/#{i}.txt",resp1.body,mode:"wb");
pp "processed #{i}";
#sleep(0.1);
}
#binding.irb;

