# 🧠 **Essencial**

> 📚 **Biblioteca prática em C para manipulação de strings e leitura de arquivos/entradas em UTF-8 no Windows**.

<div align="center"> 
  <img src="https://img.shields.io/badge/license-MIT-green?style=for-the-badge" alt="License: MIT">
  <img src="https://img.shields.io/badge/platform-Windows-blue?style=for-the-badge&logo=windows" alt="Platform: Windows">
  <img src="https://img.shields.io/badge/status-Em%20Desenvolvimento-orange?style=for-the-badge" alt="Status: Em Desenvolvimento">
  <img src="https://img.shields.io/badge/UTF--8-Compatible-brightgreen?style=for-the-badge" alt="UTF-8 Support">
</div>

![Header](https://user-images.githubusercontent.com/yourusername/banner-projeto.png)

## ✨ Recursos

✅ Leitura segura de arquivos `.txt` com suporte UTF-8  
✅ Leitura de entrada do console com acentos e caracteres especiais (ex: João, ç, á)  
✅ Substituição inteligente de texto delimitado por caracteres  
✅ Compatível com `Windows Terminal`, `CMD` e `PowerShell`  
✅ Fácil de integrar com projetos C nativos

---

## 💻 Exemplo de uso

### 📥 Leitura de arquivos UTF-8

```c
char *conteudo = readArquivoUTF8("texto.txt");
if (conteudo) {
    printf("Arquivo:\n%s\n", conteudo);
    free(conteudo);
}
```

### ⌨️ Entrada do usuário com acentos

```c
char nome[100];
readUtf8(nome, 100);
printf("Você digitou: %s\n", nome);
```

### 🧩 Substituição entre delimitadores

```c
char frase[100] = "Resultado é [x]!";
replace(frase, "42", '[', ']');
// Saída: Resultado é 42!
```
---

### 🧠 Arquitetura do Projeto

📁 **essencial.h** 
  - Definições e declarações

📁 **essencial.c**
  - Implementações completas

---

### 🛠️ Como compilar

1. **Clone o repositório**:
   ```bash
   git clone https://github.com/doutorwho/EssencialEmC.git
   cd EssencialEmC
   
2. **Compile e execute o projeto**:
    ```bash
    gcc main.c essencial.c programa.exe; .\\programa.exe

> 💡 Dica: Certifique-se de que o GCC (como o do MSYS2 ou MinGW) está instalado e configurado no PATH do sistema. Isso garante que você consiga compilar e rodar o projeto diretamente do terminal.

---

### 🌍 Contribuições são bem-vindas!

Este projeto é editável, modular e feito com foco didático e prático. Se você quer ajudar a melhorar manipulação de strings em C ou deseja expandir para Linux/macOS, junte-se a nós!

- Fork o projeto
- Crie sua branch: git checkout -b nova-funcionalidade
- Commit suas mudanças: git commit -m 'feat: nova função'
- Faça um push: git push origin nova-funcionalidade
- Envie um Pull Request 🎉

---

### 📝 Licença

Distribuído sob a licença MIT. Veja LICENSE para mais detalhes.


