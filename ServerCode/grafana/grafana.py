#copied_file = "3Przeplywomierze-1596632933790.json"
'''
skrypt odpowiada za zamiane danych wewnatrz jsonowskiego pliku pobranego z 
grafany w tym wypadku jest to 3przeplywomierze-12391230190283199
Zamieniane sa wartosci odpowiadajace za nazwe tabeli 'measurement' 
tytul wykresu, oraz uniquekey generowany na podstawie wzorcowego i dodawane sa 
kolejne znaki. 
'''

import os
import json

def swap_db(measurement,title,uniquekey):
    
    # plik odpowiada za zrzut z pierwszego stworzonego dashboarda
    # mozna pobrac kolejny z grafany tylko należy zmienic dane "ukryte"
    # w jsonie czyli nazwe measurement, klucz unikalny i tytul glowny panelu
    with open('3Przeplywomierze-1596632933790.json') as f:
        data = json.load(f) 
    
    with open('temp.txt','w') as outfile:
        json.dump(data,outfile)
    
    with open('temp.txt', 'r') as file :
        filedata = file.read()
        
    uniquekey ='Ky1ywzSGk'+str(uniquekey)

    filedata = filedata.replace('237',measurement)
    filedata = filedata.replace('3Przeplywomierze',title)
    filedata = filedata.replace('Ky1ywzSGk',uniquekey)
    
    with open('temp.txt','w') as file:
        file.write(filedata)
    
    json_data = filedata
    json_object=json.loads(json_data)
    #nazwa tworzonego pliku to nazwa tabeli np. 237.json
    name = str(measurement)+'.json'
    with open(name,'w', encoding='utf-8') as out:
        json.dump(json_object,out,ensure_ascii=False,indent=2)

    #usuwanie tymczasowego pliku przechowujacego dane z konwersji 
    if os.path.exists("temp.txt"):
        os.remove("temp.txt")
    else:
        print("The file does not exist")
        
swap_db('16','Trzeci',666)

