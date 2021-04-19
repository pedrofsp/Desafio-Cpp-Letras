/**********************************************************************************************************************
    Codigo por: Pedro Henrique Falleiros Sampaio Presotto

    Descricao do algoritimo:

    1.Introdução sobre o algoritmo:

    O algoritimo é composto por um total de 6 funções: GenerateScore, CompareCharLetters, SameCharLetters,
SortWord, UnusedLetters e a função principal. Alem das funcoes o algoritimo tambem se ultiliza 
da estrutura de Dados pilha, alem da struct classBiggestWord e a biblioteca <fstream> possibilitando 
a leitura de arquivos.

    2.A estrutura de dados pilha:

    Alem das funcoes comuns de qualquer implementacao de pilha como, Pop, Push, GetSize e etc, a pilha
tambem conta com as funcoes SetOriginalWord e GetOriginalWord que servem justamente para manipular uma
variavel private originalWord(string), que serve como backup de uma palavra em seu formato original.

    3.Descrevendo funcoes:
    
        3.1-GenerateScore: funcao que recebe uma palavra (string ou vetor de char) e analisa letra por 
letra, fazendo a soma da pontuacao(int), retornada ao fim da operacao.

        3.2-CompareCharLetters: recebe duas letras (char), e retorna true caso a primeira seja menor que a 
segunda, de acordo com a ordem alfabetica e desconsiderando caixa alta.

        3.3-SameCharLetters: recebe duas letras e retorna true caso as duas sejam as mesmas, desconsiderando
caixa alta.

        3.4-SortWord: funcao baseada em Selection Sort, recebe uma palavra(string) e altera suas
letras de forma a deixa-la organizada em ordem alfaberica.

        3.5-UnusedLetters: funcao recebe duas palavras(string) e retorna quais letras da segunda sobram
apos a primeira ser formada.

    4.Funcao principal:

    A principal comeca setando algumas variaveis e vetores. Primeiro, o vetor do tipo Stack(pilha) wordsArray,
que armazena as palavras que serao validas no jogo. As strings auxWord e auxSortedWord que apenas servem
para preencher o bancoDePalavras. O objeto biggestWord, que apenas serve para armazenar a palavra de maior 
pontuacao possivel de ser formada (iniciada com pontuacao = 0). E por ultimo as variaveis arraySize, que 
se refere ao tamanho do banco de palavras e variavel auxScore, que e apenas uma variavel auxiliar.

    Na sequencia, o algoritimo le dados de um arquivo txt externo, que possui todas as palavras do jogo. Sendo 
assim, cada pilha de cada posicao do bancoDePalavras e preenchida com as palavras  devidamente ordenadas, ao 
mesmo tempo, cada posicao tambem recebe a palavra em seu formato original (originalWord).

    Continuando, o algoritimo pega as letras da entrada e as ordena imediatamente para facilitar comparacoes
nos proximos passos. Em seguida, um for roda o vetor bancoDePalavras pilha por pilha e um segundo for (interno
ao ja citado) roda as letras da palavra de entrada. A cada verificacao de que uma letra da palavra de entrada 
seja igual a que esta no topo da pilha daquela posicao do vetor, ocorre um desempilhmento da pilha em questao.

    Ao fim do processo, caso aquela pilha esteja vazia, conclui-se que foi possivel formar aquela palavra. 
Portanto o algoritimo calcula se a pontuacao formada pela palavra em questao e maior que a maior palavra 
atual e, em caso afirmativo, atualiza a maior palavra. Concluindo, o algoritimo exibe ao usuario a maior
palavra possivel de ser formada e as letras que sobraram da entrada.

******************************************************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

//---------------------------IMPLEMENTACAO DA ESTRUTURA DE DADOS PILHA---------------------------

class Node
{
    friend class Stack;

private:
    char data;
    Node *next_pt;

public:
    Node(char value);
    ~Node(){};
};

Node::Node(char value)
{
    data = value;
    next_pt = NULL;
}

class Stack
{
private:
    string originalWord;
    Node *Top;
    unsigned size;

public:
    void SetOriginalWord(string value);
    string GetOriginalWord();
    void Push(char value);
    char Pop();
    char Spy();
    unsigned GetSize();
    bool IsEmpty();
    Stack();
    ~Stack();
};

Stack::Stack()
{
    Top = NULL;
    size = 0;
}

Stack::~Stack()
{
    while (!IsEmpty())
    {
        Pop();
    }
}

void Stack::SetOriginalWord(string value)
{
    originalWord = value;
}

string Stack::GetOriginalWord()
{
    return originalWord;
}

unsigned Stack::GetSize()
{
    return size;
}

char Stack::Spy()
{
    if (IsEmpty())
    {
        return '#';
    }
    else
    {
        return Top->data;
    }
}

bool Stack::IsEmpty()
{
    return (size == 0);
}

void Stack::Push(char value)
{
    Node *new_node = new Node(value);
    new_node->next_pt = Top;
    Top = new_node;
    size++;
}

char Stack::Pop()
{
    if (IsEmpty())
    {
        cout << "The stack`s empty \n";
        return '0';
    }
    else
    {
        char aux_value = Top->data;
        Node *aux_node = Top;
        Top = aux_node->next_pt;
        delete aux_node;
        size--;
        return aux_value;
    }
}

//-----------------------------------------------------------------------------------------------

struct classBiggestWord //struct feito para guardar a maior palavra e sua respectiva pontuacao
{
    string word;
    int score;

    classBiggestWord()
    {
        word = "palavraDefault_(nao_foi_possivel_formar_palavras)";
        score = 0;
    }
};

int GenerateScore(string word) //funcao que retorna a pontuacao de uma palavra
{
    int totalScore = 0;

    for (long unsigned int i = 0; i < word.size(); i++)
    {
        if ((word[i] == 'E') || (word[i] == 'A') || (word[i] == 'I') || (word[i] == 'O') || (word[i] == 'N') || (word[i] == 'R') || (word[i] == 'T') || (word[i] == 'L') || (word[i] == 'S') || (word[i] == 'U') || (word[i] == 'e') || (word[i] == 'a') || (word[i] == 'i') || (word[i] == 'o') || (word[i] == 'n') || (word[i] == 'r') || (word[i] == 't') || (word[i] == 'l') || (word[i] == 's') || (word[i] == 'u'))
            totalScore += 1;
        else if ((word[i] == 'W') || (word[i] == 'D') || (word[i] == 'G') || (word[i] == 'w') || (word[i] == 'd') || (word[i] == 'g'))
            totalScore += 2;
        else if ((word[i] == 'B') || (word[i] == 'C') || (word[i] == 'M') || (word[i] == 'P') || (word[i] == 'b') || (word[i] == 'c') || (word[i] == 'm') || (word[i] == 'p'))
            totalScore += 3;
        else if ((word[i] == 'F') || (word[i] == 'H') || (word[i] == 'V') || (word[i] == 'f') || (word[i] == 'h') || (word[i] == 'v'))
            totalScore += 4;
        else if ((word[i] == 'J') || (word[i] == 'X') || (word[i] == 'j') || (word[i] == 'x'))
            totalScore += 8;
        else if ((word[i] == 'Q') || (word[i] == 'Z') || (word[i] == 'q') || (word[i] == 'z'))
            totalScore += 10;
    }
    return totalScore;
}

bool CompareCharLetters(char l1, char l2) //funcao que compara se a primeira letra e menor que a segunda (em questoes de ordem alfabetica)
{
    short unsigned int v1, v2;
    v1 = (int)l1;
    v2 = (int)l2;

    if (v1 < 91) //desconsidera Caixa Alta
        v1 += 32;
    if (v2 < 91)
        v2 += 32;

    if (v1 < v2)
        return true;
    return false;
}

bool SameCharLetters(char l1, char l2) //funcao que retorna true caso a primeira letra e a segunda sejam a mesma
{
    short unsigned int v1, v2;
    v1 = (int)l1;
    v2 = (int)l2;

    if (v1 < 91) //desconsidera Caixa Alta
        v1 += 32;
    if (v2 < 91)
        v2 += 32;

    if (v1 == v2)
        return true;
    return false;
}

void SortWord(string &word)
{
    int stringSize = word.size(), smallerPos;
    char aux;
    for (int posind = 0; posind < stringSize - 1; posind++)
    {
        smallerPos = posind;
        for (int j = posind + 1; j < stringSize; j++)
        {
            if (word[j] < word[smallerPos])
            {
                smallerPos = j;
            }
        }
        aux = word[smallerPos];
        word[smallerPos] = word[posind];
        word[posind] = aux;
    }
}

void UnusedLetters(string biggestWord, string inputWord)
{
    if (biggestWord != "palavraDefault_(nao_foi_possivel_formar_palavras)")
    {
        Stack auxStack;
        SortWord(biggestWord);
        for (int i = biggestWord.size(); i > -1; i--)
        {
            auxStack.Push(biggestWord[i]); //empilhei tudo
        }
        int i = 0;
        while (!auxStack.IsEmpty())
        {
            if (SameCharLetters(auxStack.Spy(), inputWord[i])) //se as letras sao diferentes
            {
                auxStack.Pop();
            }
            else
            {
                cout << inputWord[i] << " ";
            }
            i++;
        }
    }
    else
    {
        for (long unsigned int i = 0; i < inputWord.size(); i++)
        {
            cout << inputWord[i] << " ";
        }
    }
}

int main()
{
    Stack wordsArray[71];
    string auxWord, auxSortedWord;
    classBiggestWord biggestWord;
    int arraySize = 0, auxScore;
    ifstream f1("banco_de_palavras.txt");

    while (getline(f1, auxWord))
    {
        auxSortedWord = auxWord;
        SortWord(auxSortedWord);
        wordsArray[arraySize].SetOriginalWord(auxWord);
        for (int i = auxWord.size() - 1; i > -1; i--)
        {
            wordsArray[arraySize].Push(auxSortedWord[i]);
        }
        arraySize++;
    }

    f1.close();

    string inputWord;
    cout << "# Digite as letras disponíveis nesta jogada: ";
    cin >> inputWord;
    cout << "# \n";

    SortWord(inputWord);                //ordeno as letras da entrada
    for (int i = 0; i < arraySize; i++) //apenas rodo o vetor de palavras
    {
        for (long unsigned int j = 0; j < inputWord.size(); j++) //vou rodar a palavra de entrada
        {
            if (SameCharLetters(inputWord[j], wordsArray[i].Spy())) //se a letra for igual ao topo da pilha
            {
                wordsArray[i].Pop(); // desempilha
            }
        }
        if (wordsArray[i].IsEmpty()) //se ao fim do processo aquela pilha esta vazia, vamos verificar sua pontuacao
        {
            auxScore = GenerateScore(wordsArray[i].GetOriginalWord());
            if (auxScore > biggestWord.score) //caso a pontuacao seja maior que a maior
            {
                biggestWord.word = wordsArray[i].GetOriginalWord(); //ela passa a ser a maior palavra
                biggestWord.score = auxScore;
            }
            else if (auxScore == biggestWord.score) //caso de empate
            {
                if (wordsArray[i].GetOriginalWord().size() < biggestWord.word.size())
                {
                    biggestWord.word = wordsArray[i].GetOriginalWord(); //ela passa a ser a maior palavra
                    biggestWord.score = auxScore;
                }
            }
        }
    }

    cout << "# " << biggestWord.word << ", "
         << "palavra de " << biggestWord.score << " pontos\n";
    cout << "# Sobraram: ";
    UnusedLetters(biggestWord.word, inputWord);
    cout << "\n";
    return 0;
}
