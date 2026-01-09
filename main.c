#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <math.h>
#include <conio.h>
#pragma comment (lib, "winmm.a")

#define C 261.63
#define D 293.66 // peguei do google
#define E 329.63
#define F 349.23
#define G 392.00
#define A 440.00
#define B 493.88
#define C2 523.25


float notas_musicais[7] = {C, D, E, F, G, A, B};

typedef struct {

    char chunk_id[4]; // RIFF
    int chunk_size;
    char format[4]; // contem wave escrito

    char subChunk1_id[4]; // contem fmt escrito
    int subChunk1_size;
    short audio_format;
    short numChannel;
    int sample_rate; // velocidade de amostragem: 8000 samples/sec; 44100 samples/sec; etc.
    int byte_rate; // == sample_rate *  NumChannel * bits_per_sample/8
    short block_align; // tamanho em bytes de uma sample
    short bits_per_sample; // normalmente 2bytes.

    char subChunk2_id[4]; // contem DATA escrito
    int subChunk2_size; // numero de bytes no audio em si == numSamples * numChannels * bits_per_sample/8

} audio_header;

void gerar_notas_musicais(void){

    /*Essa funcao criara as notas musicais
      em arquivos .wav*/

    /*Como uma nota é basicamente uma entonação de uma mesma
      frequencia em uma onda, basta gerarmos tal onda em um arquivo .wav*/

    /*Decidi criar uma onda cossenoidal para cada frequencia,
      que segue a equacao de elongacao do MHS: x(t) = A.cos(w.t + @)
                                               x(t) = A.cos(2πf.t)       w = 2πf
        sendo:
                A = amplitude (volume)
                f = frequnecia (altura)
                t = tempo decorrido
                *(nosso caso teremos que dividir samples por samples/segundo para obter segundo)
    */


    // primeiro vamos popular o cabecalho do arquivo .wav da onda

    audio_header notes_wavh;

    const int sample_rate = 44100; // qualidade alta
    const int tempo_duracao = 4; // 1 segundo para dar tempo de reproduzir a nota // edit: 4 segundos para ressoar o som
    const int tamanho_buffer = sample_rate * tempo_duracao; // nos dara o numero de samples totais no buffer
    short int buffer[tamanho_buffer]; // cria um buffer temporario para podermos armazenar as samples

    strcpy(notes_wavh.chunk_id, "RIFF");
    strcpy(notes_wavh.format, "WAVE");
    strcpy(notes_wavh.subChunk1_id, "fmt ");
    strcpy(notes_wavh.subChunk2_id, "data");

    notes_wavh.numChannel = 1; // 1 para mono
    notes_wavh.audio_format = 1; // 1 para PCM
    notes_wavh.subChunk1_size = 16;
    notes_wavh.bits_per_sample = 16; // 2bytes por sample
    notes_wavh.sample_rate = sample_rate;
    notes_wavh.byte_rate = sample_rate * notes_wavh.numChannel * (notes_wavh.bits_per_sample/8); // bytes por segundo
    notes_wavh.block_align = notes_wavh.numChannel * (notes_wavh.bits_per_sample/8); // bytes por sample

    /*

    EXPLICANDO COMO CHEGUEI NA EQUACAO DE SUBCHUNK2SIZE

     subChunk2_size == NumSamples * NumChannels * BitsPerSample/8
     tempo = subChunk2_size /  (SampleRate * NumChannels * BitsPerSample/8)

     -> NumSamples = SampleRate * Tempo = [samples/sec x sec]
     -> subChunk2_size = (SampleRate * Tempo) * NumChannels * BitsPerSample/8

     */

    notes_wavh.subChunk2_size = (sample_rate * tempo_duracao) * notes_wavh.numChannel * (notes_wavh.bits_per_sample/8);
    notes_wavh.chunk_size = 36 + notes_wavh.subChunk2_size;

    // agora que temos o cabecalho, precisamos encher o buffer para entao salvar em um arquivo .wav
    for (int nota = 0; nota < 7; nota++){

        for (int i = 0; i < tamanho_buffer; i++){ // percorre todo o buffer

            float t = (float)i / sample_rate; // tempo em segundos
            float volume = 10000 * pow(M_E, (-0.77*t));// 10000 * e^(-0.77t)

            // 10000: amplitude maxima
            // 0.77: constante de decaimento (genericamente 0.77 em um piano)
            // v(t) = A*e^(-@t)

            buffer[i] = (short int)(cos(2 * M_PI * notas_musicais[nota] * t) * volume); // preenche cada espaco no buffer com um valor entre -1 e 1 multiplicado por 1000x
                    //short int = 2bytes
        }

        switch (nota){

            case 0:{ // do

                FILE *arquivo_nota = fopen("do.wav", "wb");

                fwrite(&notes_wavh, sizeof(audio_header), 1, arquivo_nota); // escreve o cabecalho
                fwrite(buffer, sizeof(short int), tamanho_buffer, arquivo_nota);
                // quero escerver o buffer, sendo que cada elemento tem 2bytes, sendo 176400 elementos, dentro do arquivo_nota.

                printf("%d\n",sizeof(audio_header));
                printf("%d \ %d", sizeof(buffer), tamanho_buffer);

                fclose(arquivo_nota);
            }break;

            case 1:{ //re

                FILE *arquivo_nota = fopen("re.wav", "wb");

                fwrite(&notes_wavh, sizeof(audio_header), 1, arquivo_nota); // escreve o cabecalho
                fwrite(buffer, sizeof(short int), tamanho_buffer, arquivo_nota);

                fclose(arquivo_nota);

            }break;

            case 2:{ //mi

                FILE *arquivo_nota = fopen("mi.wav", "wb");

                fwrite(&notes_wavh, sizeof(audio_header), 1, arquivo_nota); // escreve o cabecalho
                fwrite(buffer, sizeof(short int), tamanho_buffer, arquivo_nota);

                fclose(arquivo_nota);

            }break;

            case 3:{ //fa

                FILE *arquivo_nota = fopen("fa.wav", "wb");

                fwrite(&notes_wavh, sizeof(audio_header), 1, arquivo_nota); // escreve o cabecalho
                fwrite(buffer, sizeof(short int), tamanho_buffer, arquivo_nota);

                fclose(arquivo_nota);

            }break;

            case 4:{ //sol

                FILE *arquivo_nota = fopen("sol.wav", "wb");

                fwrite(&notes_wavh, sizeof(audio_header), 1, arquivo_nota); // escreve o cabecalho
                fwrite(buffer, sizeof(short int), tamanho_buffer, arquivo_nota);

                fclose(arquivo_nota);

            }break;

            case 5:{ //la

                FILE *arquivo_nota = fopen("la.wav", "wb");

                fwrite(&notes_wavh, sizeof(audio_header), 1, arquivo_nota); // escreve o cabecalho
                fwrite(buffer, sizeof(short int), tamanho_buffer, arquivo_nota);

                fclose(arquivo_nota);

            }break;

            case 6:{ //si

                FILE *arquivo_nota = fopen("si.wav", "wb");

                fwrite(&notes_wavh, sizeof(audio_header), 1, arquivo_nota); // escreve o cabecalho
                fwrite(buffer, sizeof(short int), tamanho_buffer, arquivo_nota);

                fclose(arquivo_nota);

            }break;
        }

    }

}

audio_header wavh;

void print_audio_info(char *nome, FILE *ponteiro_audio){

    if (ponteiro_audio == NULL) {
        printf("Erro: não foi possível abrir o arquivo %s\n", nome);
        return;
    }

    printf("\n\nNome do arquivo: %s", nome);
    fread(&wavh, sizeof(wavh), 1, ponteiro_audio);

    printf("\nchunck_id       | %c%c%c%c", wavh.chunk_id[0], wavh.chunk_id[1], wavh.chunk_id[2], wavh.chunk_id[3]);
    printf("\nchunck_size     | %d", wavh.chunk_size);
    printf("\nformat          | %c%c%c%c", wavh.format[0], wavh.format[1], wavh.format[2], wavh.format[3]);
    printf("\nsubChunck1_id   | %c%c%c%c", wavh.subChunk1_id[0], wavh.subChunk1_id[1], wavh.subChunk1_id[2], wavh.subChunk1_id[3]);
    printf("\nsubChunck1_size | %d", wavh.subChunk1_size);
    printf("\naudio_format    | %d", wavh.audio_format);
    printf("\nNumChannel      | %d", wavh.numChannel);
    printf("\nSample_rate     | %d", wavh.sample_rate);
    printf("\nblock_align     | %d", wavh.block_align);
    printf("\nbits_per_sample | %d", wavh.bits_per_sample);
    printf("\nsubChunck2_id   | %s", wavh.subChunk2_id);
    printf("\nsubChunck2_size | %d", wavh.subChunk2_size);

    float duracao = (float)wavh.subChunk2_size / (wavh.sample_rate * wavh.numChannel * wavh.bits_per_sample / 8);
    printf("\nDuração do áudio: %.2f segundos\n", duracao);

}



void menu(void){

    printf("\n\n===================LORENZO 4311=============");
    printf("\n\n1. Ouvir áudio baixado.");
    printf("\n\n2. Extrair uma parte do audio, criando um novo arquvio, escolhendo um intervalo de tempo, onde se deve escolher o intervalo inicial e o final.");
    printf("\n3. Alterar o volume do audio (quantos porcento, de 1 a 300)");
    printf("\n4. Tocar piano com o teclado kkkkkk");
    printf("\n\nPOR FAVOR, SELECIONE UMA OPCAO: ");

}

void cortar_audio(FILE *audio_principal, int inicio, int fim){

    int samples_inicio = inicio * wavh.sample_rate * wavh.numChannel; // define a quantidade de samples iniciais
    int samples_fim = fim * wavh.sample_rate * wavh.numChannel; // define a quantidade de samples finais
    int samples_a_serem_lidas = samples_fim - samples_inicio;

    FILE *audio_cortado = fopen("audio_cortado.wav", "wb");

    audio_header wavh_cortado = wavh; // passa todas as informacoes do arquivo principal para uma estrutura que sera usada no novo arquivo
    wavh_cortado.subChunk2_size = samples_a_serem_lidas * (wavh.bits_per_sample / 8); // é preciso atualizar o tamanho do novo arquivo pois ele possui menos samples, logo, menos bytes
    wavh_cortado.chunk_size = 36 + wavh_cortado.subChunk2_size; // o tamanho total do arquivo sera o tamanho do RIFF e do fmt + o tamanho de "data"

    fwrite(&wavh_cortado, sizeof(wavh_cortado), 1, audio_cortado); // escreve todas as informacoes da estrutura no novo arquivo
    // (agora fwrite avancou o ponteiro 'audio_cortado' até o subchunk de 'data')

    fseek(audio_principal, (sizeof(wavh) + samples_inicio * (wavh_cortado.bits_per_sample/8)), SEEK_SET); // coloca o ponteiro de arquivo a partir da parte que queremos pegar as amostras

    short sample_atual;

    for (int qual_sample = 0; qual_sample < samples_a_serem_lidas; qual_sample++){ // como o ponteiro do audio_cortado esta no subchunk de data, agora ele vai começar a operar a partir dele
        fread(&sample_atual, sizeof(sample_atual), 1, audio_principal); // le do audio_principal, o qual o ponteiro esta apontado para 'data'
        fwrite(&sample_atual, sizeof(sample_atual), 1, audio_cortado); // escreve o sample atual no 'data' no audio_cortado
    }

    fclose(audio_cortado);

}


void alterar_volume(FILE *audio_principal, float volume){

    short sample; // variavel int de 2 bytes de tamanho, ja que sao 16 bits/samlple

    FILE *audio_volume_alterado = fopen("volume_alterado.wav", "wb");
    fwrite(&wavh, sizeof(wavh), 1, audio_volume_alterado); // passa todas as informacoes de cabecalho para o novo arquivo

    fseek(audio_principal, sizeof(wavh), SEEK_SET); // avanca o ponteiro do audio principal para os bytes alem do cabecalho
    while (fread(&sample, sizeof(sample), 1, audio_principal)){
        sample = (short)(sample * volume/100);
        fwrite(&sample, sizeof(sample), 1, audio_volume_alterado); // escreve no novo arquivo os samples com amplitude variada
    }

    printf("\nVOLUME ALTERADO EM %.0f%%!", volume);

    fclose(audio_volume_alterado);

}

int main(){

    char nome_audio[10];
    printf("\nPor favor, digite o nome do audio a ser aberto: ");
    gets(nome_audio);
    strcat(nome_audio, ".wav"); // adiciona a extensao .wav ao nome do arquvio a ser aberto

    while (1){

        FILE *audio_principal = fopen(nome_audio, "rb");
        if (audio_principal == NULL){
            printf("XXXXXXXXXXXX ERRO!!!!! XXXXXXXXXXXXXXXXXX");
            return 3;
        }

        fread(&wavh, sizeof(wavh), 1, audio_principal); // joga tudo pra struct wavh
        //print_audio_info(nome_audio, audio_principal); // debug

        int op;
        menu();
        scanf("%d", &op);
        fflush(stdin);

        switch(op){

            case 0: {


            }break;

            case 1: {

                printf("\nTocando o arquivo %s!", nome_audio);
                PlaySound(TEXT(nome_audio), NULL, SND_ASYNC);

            }break;

            case 2:{

                int ini;
                int fim;

                printf("\nA partir de quantos segundos deseja ouvir o audio?: ");
                scanf("%d", &ini);

                printf("\nDepois de quantos segundos deseja parar de ouvir o audio?: ");
                scanf("%d", &fim);

                cortar_audio(audio_principal, ini, fim);

                int tempo = fim - ini;
                printf("\nArquivo salvo em 'audio_cortado.wav'.\nSeu arquivo ficou com %d segundos!", tempo);

            }break;

            case 3:{

                float volume;

                printf("\n\nPor favor, digite a porcentagem em que deseja alterar o volume: ");
                fflush(stdin);
                scanf("%f", &volume);

                alterar_volume(audio_principal, volume);

                char sn;
                printf("\nDeseja ouvir o audio com volume alterado [s/n]?: ");
                fflush(stdin);
                scanf("%c", &sn);

                if (sn == 's' || sn == 'S'){
                    PlaySound(TEXT("volume_alterado.wav"), NULL, SND_ASYNC);
                    printf("Pressione qualquer tecla!\n");
                    getch();
                }
                else printf("\nArquivo salvo como 'volume_alterado.wav'!");

            }break;

            case 4:{

                gerar_notas_musicais();

                printf("\nPressione 'ESC' para sair!!\n\n");

                printf("\t\t\t.____________________________\n"
                       "\t\t\t|  | | | |  |  | | | | | |  |\n"
                       "\t\t\t|  | | | |  |  | | | | | |  |\n"
                       "\t\t\t|  | | | |  |  | | | | | |  |\n"
                       "\t\t\t|  |_| |_|  |  |_| |_| |_|  |\n"
                       "\t\t\t|   |   |   |   |   |   |   |\n"
                       "\t\t\t| D | F | G | H | J | K | L |\n"
                       "\t\t\t|___|___|___|___|___|___|___|\n");


                while (1){
                    if (kbhit()){

                        char tecla = getch();

                        switch(tecla){
                            case 'd':

                                printf("\nDo!");
                                PlaySound(TEXT("do.wav"), NULL, SND_ASYNC);
                                break;

                            case 'f':

                                printf("\nRe!");
                                PlaySound(TEXT("re.wav"), NULL, SND_ASYNC);
                                break;

                            case 'g':

                                printf("\nMi!");
                                PlaySound(TEXT("mi.wav"), NULL, SND_ASYNC);
                                break;

                            case 'h':

                                printf("\nFa!");
                                PlaySound(TEXT("fa.wav"), NULL, SND_ASYNC);
                                break;

                            case 'j':

                                printf("\nSol!");
                                PlaySound(TEXT("sol.wav"), NULL, SND_ASYNC);
                                break;

                            case 'k':

                                printf("\nLa!");
                                PlaySound(TEXT("la.wav"), NULL, SND_ASYNC);
                                break;

                            case 'l':

                                printf("\nSi!");
                                PlaySound(TEXT("si.wav"), NULL, SND_ASYNC);
                                break;

                            case 27:
                                printf("\nVOLTE SEMPRE!");
                                break;
                        }
                    }
                }

            }break;


        }
        fclose(audio_principal);

    }
    return 0;
}
