### How it works?

1. You need to make .html page, using template anchors, like {0}, {1}, {2}, etc. View example file **/bin/template/test_template.html**.
2. Make recipient list with variables values. It should look like simple .txt file. You can generate it though **Export** from your Data Base. View example file **/bin/list/test_list.txt
3. Launch **mailsender**, pass html template and list like arguments. 

    bin > mailsender.exe list/test_list.txt template/test_template.html Subject