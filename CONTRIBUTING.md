## Contribuindo para o simple-games

Existem várias maneiras de contribuir para o simple-games:

 - Criando um jogo novo usando a sua linguagem de preferência;
 - Resolvendo um dos [issues](https://github.com/jibaky/simple-games/issues) do projeto;
 - Aprimorando um jogo já submetido ou adicionando documentações.

### Pré-requisitos
Para contribuir com o projeto, você precisa de:

 - Uma conta no GitHub 😉
 - Git instalado no seu computador ([guia de instalação bem aqui](https://help.github.com/en/articles/set-up-git))
 - Uma linguagem de programação

## Começando os trabalhos

### Crie um fork do repositório (`fork`)
Crie um fork do repositório usando o botão no canto superior direito da tela e aguarde a criação do novo repositório.

### Cire o repositório local (`git clone`)
Em seguida, para criar o seu repositório local onde as alterações serão feitas, use o comando `git clone https://github.com/<seu_username>/simple-games.git`. Ele criará uma cópia do seu fork nos arquivos locais do computador (na pasta onde o comando foi executado no console) para edição.

### Escolhendo uma linguagem
Verifique na pasta `linguagens` se já existe a pasta da linguagem que você escolheu. **Caso ela já não exista**, crie uma pasta com o nome da linguagem (ex.: "c", "c-sharp", "javascript", etc).

### Criando a pasta do jogo
Dentro da pasta da linguagem escolhida, crie uma pasta com o nome do jogo, seguindo as regras abaixo:

 - Use apenas letras minúsculas
 - Não use acentos
 - Use *hífens* ao invés de espaços (*jogo-da-velha*)

A estrutura da sua pasta deve ser, por exemplo:

```
c
├── jogo-da-velha
	├── README
	├── src
```
O arquivo README precisa conter as informações do jogo e como executá-lo, enquanto a pasta `src` deve conter os códigos e pastas necessários para a execução do jogo.

### Submetendo um novo jogo
Para submeter um novo jogo, use os comandos
```git
git checkout -b <linguagem>/<nome-do-jogo>
git add <linguagem>/<nome-do-jogo>
git commit -m "feat(jogo): adding <linguagem>/<nome-do-jogo>"
git push origin <linguagem>/<nome-do-jogo>
```

*Se você não está conseguindo fazer o push, talvez precise sincronizar seu fork com o upstream. Para isso, siga [esse passo](https://docs.github.com/en/free-pro-team@latest/github/collaborating-with-issues-and-pull-requests/configuring-a-remote-for-a-fork), e depois [esse](https://docs.github.com/en/free-pro-team@latest/github/collaborating-with-issues-and-pull-requests/syncing-a-fork)!*

Em seguida, crie uma Pull Request para o repositório principal seguindo as instruções na tela.

### Submetendo alterações para um jogo existente
Para submeter suas alterações de um jogo já existente, use os comandos
```git
git checkout -b <linguagem>/<nome-do-jogo>
git add <linguagem>/<nome-do-jogo>
git commit -m "edit(jogo): editing <linguagem>/<nome-do-jogo>"
git push origin <linguagem>/<nome-do-jogo>
```

Caso as alterações sejam **unicamente** na documentação, use os comandos
```git
git checkout -b <linguagem>/<nome-do-jogo>
git add <linguagem>/<nome-do-jogo>
git commit -m "doc(jogo): adding documentation for <linguagem>/<nome-do-jogo>"
git push origin <linguagem>/<nome-do-jogo>
```

Em seguida, crie a sua Pull Request e siga as instruções!
