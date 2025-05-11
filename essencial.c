#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

void erro_personalizado(const char *mensagem) {
    fprintf(stderr, "Erro: %s\n", mensagem);
    exit(EXIT_FAILURE);
}

/**
 * @brief Substitui uma parte de uma string delimitada por dois caracteres por um novo texto.
 *
 * A função busca por dois caracteres delimitadores (`parada1` e `parada2`) dentro da string `texto`.
 * Todo o conteúdo entre (e incluindo) `parada1` até logo após `parada2` será substituído pela string `novo_texto`.
 * O resultado final será armazenado novamente em `texto`, modificando-o diretamente.
 *
 * @param texto        A string original onde a substituição será feita. Essa string será modificada.
 * @param novo_texto   A string que substituirá o conteúdo entre os delimitadores.
 * @param parada1      O caractere inicial delimitador da seção a ser substituída.
 * @param parada2      O caractere final delimitador da seção a ser substituída.
 *
 * @note A função utiliza alocação dinâmica para construir as partes da nova string. 
 *       Certifique-se de que `texto` tenha espaço suficiente, ou use tamanhos adequados. Se texto for uma variável estática, o novo texto não pode
 *       ultrapassar.
 *
 * @note Se os delimitadores não forem encontrados, ou se a string `texto` tiver 3 ou menos caracteres,
 *       uma função de erro personalizada (`erro_personalizado`) será chamada para tratamento.
 *
 * @warning A função assume que os delimitadores aparecem uma única vez. Se aparecerem múltiplas vezes,
 *          a última ocorrência de `parada1` e `parada2` será usada.
 *
 * @example
 * char str[100] = "O valor é [x]!";
 * replace(str, "42", '[', ']');
 * // Resultado: "O valor é 42!"
 */
void replace(char texto[], char novo_texto[], char parada1, char parada2) {

    // verificação de erros
    int tamanho_string = strlen(texto);

    if (tamanho_string <= 3) {
        erro_personalizado("Texto insufuciente!");
    }


    // continuação do programa
    int p1_posi = -1, p2_posi = -1; // para questões de erro
    for (int c=0; c < tamanho_string; c++) {
        if (parada1 == texto[c]) {
            p1_posi = c;
        }
        if (parada2 == texto[c]) {
            p2_posi = c+1; // isso é para apagar a parte de "?"!
        }
    }

    // verificação de erros
    if (p1_posi == -1 && p2_posi == -1) {
        erro_personalizado("Não há nenhum caractere nesse texto!");
    }

    // continuação do programa
    // primeira parte
    char *texto_antes = (char*)malloc(sizeof(char) * p1_posi);
    memmove(texto_antes, &texto[0], p1_posi);
    texto_antes[p1_posi] = '\0';

    // segunda parte
    int tamanho_s2 =  (tamanho_string - p2_posi);
    char *texto_depois = (char*)malloc(sizeof(char) * tamanho_s2);
    memmove(texto_depois, &texto[p2_posi], tamanho_s2);
    texto_depois[tamanho_s2] = '\0';

    // última parte
    // agora só dividimos a posição
    int novo_tamanho = ((tamanho_string + strlen(novo_texto)) - (p2_posi - p1_posi) + 1);
    char *texto_atualizado = (char*)malloc(sizeof(char) * novo_tamanho);
    snprintf(texto_atualizado, novo_tamanho, "%s%s%s", texto_antes, novo_texto, texto_depois);

    // texto atualizado
    strcpy(texto, texto_atualizado);
    
}

/**
 * @brief Lê uma string UTF-8 do console (inclusive com acentuação ou caracteres como "João").
 *
 * Esta função configura o console do Windows para usar codificação UTF-8, permitindo a leitura correta
 * de caracteres acentuados ou especiais, como "ç", "á", "õ", etc. O conteúdo lido é convertido de wide-char (UTF-16)
 * para UTF-8 e armazenado na string `texto`, que é modificada diretamente.
 *
 * @param texto            Vetor de caracteres onde a string lida em UTF-8 será armazenada.
 * @param tamanho_valor    Tamanho máximo esperado da string (em quantidade de caracteres wide-char).
 *
 * @note A função realiza a leitura do console com `ReadConsoleW`, usando caracteres wide (`wchar_t`),
 *       e converte o resultado para UTF-8 usando `WideCharToMultiByte`.
 *
 * @note Utiliza alocação dinâmica para `input` (wide-char) e `utf8_input`. Esses ponteiros são temporários
 *       e a memória deve ser liberada se a função for adaptada para versões seguras. A função atual
 *       não libera a memória alocada, portanto recomenda-se revisar para evitar vazamentos em usos extensos.
 *
 * @note Caracteres de nova linha `\n` ao final da entrada são removidos automaticamente.
 *
 * @warning Esta função é específica para ambientes Windows. Não funcionará corretamente em Linux ou outros
 *          sistemas sem ajustes.
 *
 * @warning A função supõe que a string final cabe no buffer `texto`. Certifique-se de que o tamanho do vetor
 *          seja suficiente para armazenar os dados convertidos em UTF-8.
 *
 * @example
 * char nome[100];
 * readUtf8(nome, 100);
 * printf("Você digitou: %s\n", nome);
 * // Entrada: João
 * // Saída: Você digitou: João
 */
void readUtf8(char texto[], int tamanho_valor) {
    // configurações padrão
    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    
    // agora configurando para a leitura
    DWORD quantidade;
    wchar_t *input = (wchar_t*)malloc(tamanho_valor * sizeof(wchar_t));
    ReadConsoleW(GetStdHandle(STD_INPUT_HANDLE), input, 512, &quantidade, NULL);
    
    // remover caracteres de nova linha presente
    if (input[quantidade - 1] = L'\n') {
        input[quantidade - 1] = L'\0';
    }
    
    //conventer para utf-8
    int utf_len = 0; // Variável para armazenar o tamanho real da string convertida
    int tamanho_utf8 = quantidade * 2; 
    char *utf8_input = (char*)malloc(tamanho_utf8 * sizeof(char));

    utf_len = WideCharToMultiByte(CP_UTF8, 0, input, quantidade, utf8_input, tamanho_utf8, NULL, NULL);
    utf8_input[utf_len-2] = '\0'; // pra tirar o '\n'. 
    
    // atualizando o texto
    strcpy(texto, utf8_input);
}


/**
 * @brief Lê o conteúdo de um arquivo de texto codificado em UTF-8 e retorna como uma string.
 *
 * Esta função abre um arquivo no modo binário (`"rb"`), lê seu conteúdo completo e retorna
 * uma string (`char*`) alocada dinamicamente contendo os dados. Essa string está pronta para
 * uso em funções compatíveis com UTF-8.
 *
 * @param endereco_arquivo Caminho do arquivo que será lido.
 *
 * @return Retorna um ponteiro para a string contendo o conteúdo do arquivo, ou `NULL` se ocorrer erro
 *         ao abrir o arquivo ou ao alocar memória.
 *
 * @note O conteúdo retornado é terminado com `'\0'`, permitindo uso direto com funções como `printf`.
 *
 * @note A memória retornada é alocada dinamicamente com `malloc`. O usuário é responsável por liberar
 *       essa memória com `free` após o uso, para evitar vazamentos.
 *
 * @warning A função assume que o arquivo está corretamente codificado em UTF-8.
 *
 * @warning O conteúdo do arquivo será lido inteiro para a memória. Evite usar esta função
 *          com arquivos muito grandes para não causar problemas de desempenho ou estouro de memória.
 *
 * @example
 * // Exemplo de uso:
 * char *conteudo = readArquivoUTF8("teste.txt");
 * if (conteudo != NULL) {
 *     printf("Conteúdo:\n%s\n", conteudo);
 *     free(conteudo);
 * } else {
 *     printf("Erro ao ler o arquivo.\n");
 * }
 */
char* readArquivoUTF8(char endereco_arquivo[]) {
    FILE *fp = fopen(endereco_arquivo, "rb");
    if (!fp) {
        printf("Erro ao abrir o arquivo!\n");
        return NULL;
    }

    fseek(fp, 0, SEEK_END); // Move o ponteiro até o final do arquivo.
    long file_size = ftell(fp); //  Retorna o número de bytes do arquivo.
    rewind(fp); // Volta o ponteiro para o início, porque agora a gente já sabe o tamanho e vai começar a leitura.

    char *byte_copiado = (char *)malloc(file_size + 1);
    if (!byte_copiado) {
        printf("Erro ao alocar memória!\n");
        fclose(fp);
        return NULL;
    }

    fread(byte_copiado, 1, file_size, fp);
    byte_copiado[file_size] = '\0';  // Finaliza string
    fclose(fp);

    return byte_copiado;
}


int main() {
    //char texto[] = "Olá mundo, tudo bem? Somos todos Bahia!";
    //replace(texto, ", estamos bem na lagoa?", ',', '?');
    //printf("Novo texto é: %s\n", texto);
    //char texto[512];

    //printf("Digite um nome: ");
    //readUtf8(texto, 512);
    //printf("O nome é: %s\n", texto);

    char *retornar = readArquivoUTF8("teste.txt");
    printf("%s\n", retornar);
        

    return 0;
}