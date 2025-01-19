# ITP - Atividade da 3ª unidade

## ℹ️ Informações

Programa desenvolvido para gerar arquivos no formato PBM contendo códigos de barras, 
a partir de identificadores válidos fornecidos como entrada.

&nbsp;

## ☑️ Requisitos da tarefa

### 1️⃣ Gerar um arquivo PBM contendo o código de barras correspondente ao idenficador fornecido ao programa. 

- [x] O programa deve receber como argumento obrigatório (em linha de comando) o identificador a ser inserido no código de barras.
- [x] Caso não haja erro, o programa deverá gerar a imagem PBM com o código de barras.

&nbsp;

* O programa poderá receber os seguintes argumentos opcionais (em linha de comando): 
  - [x] O espaçamento lateral do código na imagem (em pixels);
  - [x] A quantidade de pixels por área do código (em pixels);
  - [x] A altura do código de barra (em pixels);
  - [x] O nome da imagem PBM a ser gerada;
  - [x] Caso o usuário não informe os argumentos opcionais, o programa adotará um valor padrão pré-definido.
 
&nbsp;
        
* Se o identificador a ser inserido não for um identificador válido, o programa deve informar o problema e parar a execução. Possíveis problemas são:
  - [x] Identificador contém valores não numéricos;
  - [x] Identificador não possui 8 dígitos;
  - [x] O dígito verificador do identificador é inválido (não corresponde aos valores anteriores);
  - [x] Se o arquivo da imagem a ser gerada já existir, o programa deverá informar que o arquivo já existe e perguntar se poderá sobrescrevê-lo. Se o usuário informar que "não", o programa deverá mostrar uma mensagem de erro ("arquivo resultante já existe") e parar a execução.

&nbsp;

### 2️⃣ Extrair o código identificador de uma imagem PBM contendo um código de barras. 
OBS: <b>Não fiz essa parte.</b>

&nbsp;

## 💻 Executar o programa

Irei fornecer o programa compactado no formato zip. Porém, caso prefira trabalhar com o repostório, ele está disponível no meu github.
[Link](https://github.com/felipeaz3vedo/itp-atividade-unidade-3)

### Etapas

1. Descompacte o arquivo .zip ou clone o repositório no diretório de sua escolha

      ```bash
      git clone https://github.com/felipeaz3vedo/itp-atividade-unidade-3.git
      ```

&nbsp;

2. Entre no diretório do projeto via linha de comando

&nbsp;


3. Compile o programa

      ```bash
      gcc -o generate main_generate.c barcode_utils.c
      ```

&nbsp;

4. Forneça os argumentos para gerar um código de barras

      ```bash
      ./generate <identificador> <espaçamento_lateral> <qtd_pixels_área> <altura> <nome_arquivo>
      ```

      &nbsp;

      | Argumento               | Obrigatório |
      |-------------------------|-------------|
      | `identificador`         | S 
      | `espaçamento_lateral`   | N 
      | `qtd_pixels_área`       | N 
      | `altura`                | N 
      | `nome_arquivo`          | N

      &nbsp;

      Exemplos: 
      
      ```bash
      ./generate 40170725
      ```
      
      ```bash
      ./generate 40170725 4 3 100 bar_code
      ```
      
&nbsp;

5. Dado um identificador válido, a imagem irá ser gerada na pasta /bar-codes

&nbsp;

7. Abra a imagem com um editor compátivel com o formato .pbm