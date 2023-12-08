# Astrid-3D
Finalmente a atualização necessária, a evolução da franquia Astrid. Agora em 3D, com uma jogabilidade mais fluida e uma experiência mais imersiva.

![Logo](assets/LOGO/astridLogo.gif)

## Como Jogar

- **Movimento:** Uso o mouse para movimentar a camera e as teclas WASD para de locomover no espaco.
- **Objetivo:** Defenda a terra dos asteroides enviados por inteligências extra-terrestres hostís.

## Requisitos

Certifique-se de que seu sistema atenda aos seguintes requisitos antes de compilar e executar o jogo:

- [Compilador C++](https://gcc.gnu.org/) instalado
- [OpenGL](https://www.opengl.org/) instalado
- [GLM](https://glm.g-truc.net/0.9.9/index.html) instalado
- [SOIL](https://github.com/littlstar/soil) instalado

## Instalação dos requisitos no Ubuntu

Para instalar os requisitos no Ubuntu ou derivados, voce pode executar o dependencies.sh que se encontra na raiz do projeto, ou seguir os passos abaixo:

1. **De as permissões necessárias para o arquivo de dependêcias:**

```bash
chmod +x dependencies.sh
```

2. **Execute o arquivo:**

```bash
./dependencies.sh
```
Caso queira instalar manualmente, siga os passos abaixo:

1. **Atualize o sistema:**

```bash
sudo apt update
sudo apt upgrade -y
sudo apt dist-upgrade -y
sudo apt autoremove -y
```

2. **Instale o compilador C++**

```bash
sudo apt install build-essential -y
```

3. **Instale o OpenGL:**

```bash
sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev -y
```

4. **Instale o GLM:**

```bash
sudo apt install libglm-dev -y
```

5. **Instale o SOIL:**

```bash
sudo apt install libsoil-dev -y
```

## Compilando e executando o jogo

Execute o seguinte comando na raiz do projeto:

```bash
make
./astrid3d
```
## Creditos

<table>
  <tr>
    <td align="center"><a href="https://github.com/ph3523"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/80484091?v=4" width="150px;" alt=""/><br /><sub><b>Pedro Barroso</b></sub></a><br /><a href="mailto:ph.barroso3523@gmail.com" title="Email">📧</a></td>
    <td align="center"><a href="https://github.com/JVictor011"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/91631521?v=4" width="150px;" alt=""/><br /><sub><b>João Victor</b></sub></a><br /><a href="mailto:joaovictor.20739@gmail.com" title="Email">📧</a></td>
    <td align="center"><a href="https://github.com/FelpLiet"><img style="border-radius: 50%;" src="https://avatars.githubusercontent.com/u/30266169?v=4" width="150px;" alt=""/><br /><sub><b>Felipe Nogueira</b></sub></a><br /><a href="mailto:felipe.leite23@gmail.com" title="Email">📧</a></td>
  </tr>
</table>

## Contribuição

**Caso encontre algum bug ou tenha alguma sugestão de melhoria, por favor, abra uma issue ou pull request ou entre em contato com um dos contribuidores. Será um prazer ter alguém contribuindo com o projeto.** 
