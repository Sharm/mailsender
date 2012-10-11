### How it works?

1. You need to make .html page, using template anchors, like {0}, {1}, {2}, etc. View example file **/bin/template/test_template.html**.
2. Make recipient list with variables values. It should look like simple .txt file. You can generate it though **Export** from your Data Base. View example file **/bin/list/test_list.txt
3. Launch **mailsender**, pass html template and list like arguments. 

    `$> mailsender.exe list/test_list.txt template/test_template.html Subject`
    
### Compile (Linux):

1. Build dependences (Socket lib). 
    * cd dep/Sockets-2.3.9.7/
    * make && make install
2. Build mailsender:
    * cd src/mailsender
    * make && make install
3. Compiled binary here: **bin/mailsender**