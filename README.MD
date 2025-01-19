# ITP - Atividade da 3ª unidade

Programa desenvolvido para gerar arquivos no formato PBM contendo códigos de barras, 
a partir de identificadores válidos fornecidos como entrada.

## Requisitos da tarefa

- [x] Gerar um arquivo PBM contendo o código de barras correspondente ao idenficador fornecido ao programa.
    - [x] O programa deve receber como argumento obrigatório (em linha de comando) o identificador a ser inserido no código de barras.
    - [x] O programa poderá receber os seguintes argumentos opcionais (em linha de comando):
        - [x] O espaçamento lateral do código na imagem (em pixels);
        - [x] A quantidade de pixels por área do código (em pixels);
        - [x] A altura do código de barra (em pixels);
        - [x] O nome da imagem PBM a ser gerada.
    - [x] Caso o usuário não informe os argumentos opcionais, o programa adotará um valor padrão pré-definido.
    - [x] Se o identificador a ser inserido não for um identificador válido, o programa deve informar o problema e parar a execução. Possíveis problemas são:
        - [x] Identificador contém valores não numéricos;;
        - [x] Identificador não possui 8 dígitos;
        - [x] O dígito verificador do identificador é inválido (não corresponde aos valores anteriores).
    - [x] Se o arquivo da imagem a ser gerada já existir, o programa deverá informar que o arquivo já existe e perguntar se poderá sobrescrevê-lo. Se o usuário informar que "não", o programa deverá mostrar uma mensagem de erro ("arquivo resultante já existe") e parar a execução
    - [x] Caso não haja erro, o programa deverá gerar a imagem PBM com o código de barras.

- [ ] Extrair o identificador do código de barras presente numa imagem PBM.

&nbsp;

## Executar o programa

Irei fornecer o programa compactado no formato ZIP. Porém, caso prefira trabalhar com o repostório, ele está disponível no meu github.
[Link](https://github.com/felipeaz3vedo/itp-atividade-unidade-3)

### Etapas

1. Descompacte o arquivo ou clone o repositório

```bash
git clone https://github.com/felipeaz3vedo/itp-atividade-unidade-3.git
```

&nbsp;

2. Entre no diretório do projeto (caso ainda não esteja dentro).

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

* Argumentos obrigatórios
    - identificador

Exemplo: 

```bash
./generate 40170725
```

* Argumentos opcionais
    - espaçamento_lateral
    - qtd_pixels_área
    - altura
    - nome_arquivo

```bash
./generate 40170725 4 3 100 bar_code
```