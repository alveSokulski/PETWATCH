# PETWATCH
Projeto feito para a disciplina de Eletrônica Aplicada.
<br><br>
O projeto consiste de um "clone" do Tamagocchi em Arduino, o que é engraçado, pois o "clone" em questão custa várias vezes mais do que o original, mas isso não importa.
<br>
Enfim, o projeto.
<br>
Usamos uma placa de Arduino NANO para construir. A ideia original era usar um Arduino UNO, mas o tamanho do produto final ficaria ridículo, isso porque não sabíamos nem que o display OLED era tão pequeno, nem o módulo RTC era tão imenso. 
<br>
Pode ser visto na pasta "código" o arquivo "sprites.h", que consiste de matrizes de números hexadecimais. Esses números são nada mais nada menos que os sprites (que podem ser vistos na pasta "sprites") codificados dentro da memória de programa do Arduino. Mais uma vez, não sabíamos que a ROM interna do Arduino não era capaz de armazenar os arquivos .bmp para serem acessados. Então, das duas uma: ou comprávamos um módulo para microchip, ou fazíamos desse jeito. Esse jeito era muito mais barato.
<br>
Por fim, após alguns meses de discussões e brigas, o projeto final foi entregue.
<br>
Por falar nisso, @fingerson ainda estás a me dever o dinheiro do OLED
