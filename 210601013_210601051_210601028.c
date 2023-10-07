#include <stdio.h>
#include <stdlib.h>

void sonuc(char x[],long int y[][3],float z,int a,float b);
void sifirla(char siyasi_partiler[]);
void turkiye_geneli_sonuc(char a[],long int b[],int d,float e,int x,long int z[][2],float f,int g,int h[][1],int k[][1]);

int main()
{
    char x;
    char siyasi_partiler[6]={'A','B','C','D','E','F'};
    int parti_sayisi=6,il_milletvekili_kontenjan;
    int sehir_birinci[10][1]={0,0,0,0,0,0,0,0,0,0};
    int mv[10][1]={0,0,0,0,0,0,0,0,0,0};
    int mv_sayisi[6]={0,0,0,0,0,0};
    int i=0,toplam_mv=0,a,b,j;
    int gecici;
    int il_plaka_kod;
    long int parti_oy[6][3]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    long int gecici_parti_oy[6]={0,0,0,0,0,0};
    long int toplam_mv_parti[6][2]={0,0,0,0,0,0,0,0,0,0,0,0};
    float toplam_oy=0,toplam_tr_oy=0;
    float oy_yuzde=0;
    float mv_yuzde=0;
    printf("----------SECIM SIMULASYONU----------\n\n\n");
    
    do
    {
    	printf("Ilin plaka kodunu giriniz:");
    	scanf("%d",&il_plaka_kod);
        printf("Ilin milletvekili kontenjanini giriniz:");
        scanf("%d",&il_milletvekili_kontenjan);
        toplam_mv+=il_milletvekili_kontenjan;
        for(i=0;i<6;i++)
        {
            printf("%c Partisi'nin oy sayisini giriniz:",siyasi_partiler[i]);
            scanf("%ld",&parti_oy[i][0]);
            toplam_oy+=parti_oy[i][0];
            gecici_parti_oy[i]+=parti_oy[i][0];
        }
        toplam_tr_oy+=toplam_oy;
        
		printf("\nMilletvekili Kontenjani : %d",il_milletvekili_kontenjan);
        printf("\nGecerli Oy Sayisi : %.0f",toplam_oy);
        for(i=0;i<6;i++)
        {
            parti_oy[i][2]=i;
            toplam_mv_parti[i][1]=i;
        }
        for(a=0;a<=6;a++)
        {
            for(b=0;b<=6;b++)
            {
                if(parti_oy[a][0]>parti_oy[b][0])
                {
                    gecici=parti_oy[a][0];
                    parti_oy[a][0]=parti_oy[b][0];
                    parti_oy[b][0]=gecici;

                    gecici=parti_oy[a][2];
                    parti_oy[a][2] = parti_oy[b][2];
                    parti_oy[b][2] = gecici;
                }
            }
        }
        for(i=0;i<6;i++)
        {
             if(parti_oy[0][2]==i)
             {
                 sehir_birinci[i][0]++;
                 break;
             }
        }
        int parti_ayarla[6][2];
        for(i=0;i<6;i++)
        {
            parti_ayarla[i][0] = parti_oy[i][0];
            parti_ayarla[i][1] = i;
        }
        do {
            for(i=0;i<6;i++)
            {
                for(j=0;j<5;j++)
                {
                    if(parti_ayarla[j][0] < parti_ayarla[j+1][0])
                    {
                        gecici = parti_ayarla[j][0];
                        parti_ayarla[j][0] = parti_ayarla[j+1][0];
                        parti_ayarla[j+1][0] = gecici;

                        gecici = parti_ayarla[j][1];
                        parti_ayarla[j][1] = parti_ayarla[j+1][1];
                        parti_ayarla[j+1][1] = gecici;
                    }
                }
            }
            il_milletvekili_kontenjan--;
            parti_oy[parti_ayarla[0][1]][1]++;
            parti_ayarla[0][0] = parti_ayarla[0][0]/2;
            
        }while(il_milletvekili_kontenjan>0);
        for(i=0;i<6;i++)
        {
             if(parti_oy[i][1]==0)
             {
                 mv[parti_oy[i][2]][0]++;
             }
        }
        printf("\n\t\tOy Say \t\tOy Yuzde \tMV Say");
        printf("\n\t\t------\t\t------\t\t------");
        sonuc(siyasi_partiler,parti_oy,oy_yuzde,parti_sayisi,toplam_oy);
        for(i=0;i<6;i++)
        {
        	toplam_mv_parti[parti_oy[i][2]][0]+=parti_oy[i][1];
		}

        printf("\nDevam etmek icin (d) tusuna basin / Turkiye Geneli Sonuc Icin (t) tusuna basin");
        scanf("%s",&x);
        
        if(x=='t')
        {   
            toplam_oy=0;
            il_milletvekili_kontenjan=0;
            for(i=0;i<6;i++)
            {
                parti_oy[i][1]=0;
            }
        }
    }
    while(x=='d');
    printf("\n\t\t\t\t----------TURKIYE GENELI SECIM SONUCLARI----------\n\n\n");
    printf("\nMilletvekili Kontenjani : %d",toplam_mv);
    printf("\nGecerli Oy Sayisi : %.0f",toplam_tr_oy);
    printf("\n\t\tOy Say \t\tOy Yuzde \t MV Say \tMV Yuzde \t Il 1.lik Say. \t 0 MV Il Say.");
    printf("\n\t\t------\t\t------\t\t------\t\t------\t\t------\t\t------");
    turkiye_geneli_sonuc(siyasi_partiler,gecici_parti_oy,parti_sayisi,oy_yuzde,toplam_tr_oy,toplam_mv_parti,mv_yuzde,toplam_mv,sehir_birinci,mv);
}

void sonuc(char x[],long int y[][3],float z,int a,float b)
{
    int c;
    for(c=0;c<a;c++)
    {
        z=(y[c][0]*100)/b;
        printf("\n%c Partisi \t%ld \t\t%.2f \t\t%ld",x[y[c][2]],y[c][0],z,y[c][1]);
    }
}
void sifirla(char siyasi_partiler[])
{
    char partiler0[6]={'A','B','C','D','E','F'};
    int i;
    for(i=0;i<6;i++)
    {
        siyasi_partiler[i]=partiler0[i];
    }
}
void turkiye_geneli_sonuc(char a[],long int b[],int d,float e,int x,long int z[][2],float f,int g,int h[][1],int k[][1])
{
    long int mv_say1[d][2];
    int i,j;
    for(i=0;i<d;i++)
    {
        mv_say1[i][0] = z[i][0];
        mv_say1[i][1] = i;
    }
    for(i=0;i<d;i++)
    {
        for(j=0;j<d-1;j++)
        {
            if(mv_say1[j][0] < mv_say1[j+1][0])
            {
                int gecici;
                gecici = mv_say1[j][0];
                mv_say1[j][0] = mv_say1[j+1][0];
                mv_say1[j+1][0] = gecici;

                gecici = mv_say1[j][1];
                mv_say1[j][1] = mv_say1[j+1][1];
                mv_say1[j+1][1] = gecici;
            }
        }
    }
    for(i=0;i<d;i++)
    {
        f= (float)(z[i][0]*100)/g;
        e=(float)(b[i]*100)/x;
        printf("\n%c Partisi \t%ld \t\t%.2f\t\t%ld\t\t%.2f\t\t%d\t\t%d",a[i],b[i],e,z[i][0],f,h[i][0],k[i][0]);
    }
    printf("\nIktidar Partisi : %c\nAna Muhalefet Partisi:%c",a[mv_say1[0][1]],a[mv_say1[1][1]]);
}
