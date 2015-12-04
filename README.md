# csvtools

Comandos simples para manipulacao rapida de arquivos CSV

csv_listid (CSVFILE)
  Lista primeira coluna de todos os registros
  
csv_getid (CSVFILE) (ID)
  Obtem linha cujo id (primeira coluna) seja igual ao ID informado
  
csv_getid_col (CSVFILE) (ID) (COL)
  Encontra linha cujo id (primeira coluna) seja igual ao ID informado, e retorna a coluna de numero COL, indice comeca em 1

csv_remove_id (CSVFILE) (ID)
  Remove um registro do arquivo CSV

