require 'faraday'

#def to_file(fname,body)
#File.write("#{fname}.epub",body,mode:"wb");
#end #to_file

audio=[14503,29450];#body.size=0, not investigated, no interrest
se=[9812,15357,3535,193638,13965,8478,8866,196101,199555,199180,212430];
books=[193638,212430];#302 redirect status
book_id=books.first;
lnk = "http://flibusta.su/book/#{book_id}/d/file/?f=epub";
req_hdr ={'User-Agent'=> #'bukLau'};
"Mozilla/5.0 (Linux; Android 16 Beta 2; Z832 Build/MMB29M) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/134.0.6998.35/36 Mobile Safari/537.36"};

conn=Faraday.new(lnk,params:nil,headers:req_hdr);

resp1=conn.get();

raw_cookies=resp1.headers["set-cookie"];
splt_cookies=raw_cookies.split(/[;,]\s?/);#regex rules

lst=[];
lst.append(splt_cookies[0]);#magic numbers
lst.append(splt_cookies[-5]);

#"Cookie: SE; rand=bl30853; lg=DE; bl30853=1;
session=splt_cookies[0];
rand_val=splt_cookies[-5].split('=').last;
#lg= #static

dl_cookie_str="#{session}; rand=#{rand_val}; lg=RU; #{rand_val}=1;"

req_hdr.store('Cookie',dl_cookie_str);
pp req_hdr;
conn.headers=req_hdr;
resp2=conn.get();
pp resp2.body.size();
pp resp2.headers;
File.write("#{book_id}.epub",resp2.body,mode:"wb");


binding.irb if (resp2.body.size < 1)
