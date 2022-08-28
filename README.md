# minitalk_42Turkey

Minitalk

Unix sisteminizde bir program çalıştırdığınızda, sistem o program için özel bir ortam yaratır. Bu ortam, sistemin, sistemde başka hiçbir program çalışmıyormuş gibi programı çalıştırması için gereken her şeyi içerir.

Her işlemin kendi -PID (işlem kimliği) vardır.


fork() işlevi, çalışan işlemi iki işleme böler; mevcut işlem ebeveyn olarak bilinir ve yeni işlem alt işlem olarak bilinir.

………………………………………….

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid;
	pid = fork();
	pid = fork();
	printf("%d Selam Dünya \n", pid);
} 

>>>>>>

70646 Selam Dünya
0 Selam Dünya
70647 Selam Dünya
0 Selam Dünya

………………………………………….


………………………………………….

#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
	int pid;
	pid = fork();
	if(pid > 0)
	{
		printf("parent\n");	
	}
	if(pid == 0)
	{
		printf("child\n");
	}
	if(pid < 0)
	{
		printf("error");
	}
}

>>>>>>

parent
child
………………………………………….


Sinyaller: Çeşitli "önemli" olaylardan haberdar olmak için bir işleme gönderilen çeşitli bildirimlerdir. Doğası gereği, sürecin yaptığı her şeyi keserler ve onu hemen işlemeye zorlarlar.

Her sinyalin kendisini temsil eden bir tamsayısının yanı sıra sembolik bir adı vardır. kill -l komutunu kullanarak sistem tarafından desteklenen sinyalleri listelemek mümkündür.

https://github.com/achrafelkhnissi/minitalk/blob/master/README/unix_signals.md

İşlemlere sinyal göndermenin bir yolu, kill sistem çağrısını kullanmaktır. Bu, bir süreçten diğerine sinyal göndermenin normal yoludur.

………………………………………….

#include <unistd.h>    
 #include <sys/types.h>
 #include <signal.h>

 int main(void)
 {
     pid_t my_pid;
     
     my_pid = getpid();
     kill(my_pid, SIGSTOP);
     return (0);
 }

>>>>>>

Bu örnek program, bir işlemin kendisine STOP sinyali göndererek kendi yürütmesini askıya almasına neden olur.

………………………………………….



signal()

int signal(int sig:qnum, void (*funct)(int));

Sinyal işareti için hata işleyicisini ayarlar. Sinyal işleyici ayarlanarak, varsayılan işleyici devreye girer (sinyal yok sayılır) veya kullanıcı tanımlı bir fonksiyon çağrılır.
Sinyallere işlem yapmak için sig parametre değeri ile bir sinyal işlemci fonksiyonu devreye sokulur.

https://github.com/achrafelkhnissi/minitalk/blob/master/README/used_funcitons.md


kill()

int kill(pid_t pid, int sig);

Herhangi bir işlem grubuna veya işleme herhangi bir sinyal göndermek için kullanılır.


pause()

int pause(void);

İşlemi sonlandıran veya bir sinyal yakalama işlevinin çağrılmasına neden olan bir sinyal teslim edilene kadar çağıran işlemin (veya iş parçacığının) uyku moduna geçmesine neden olur.

sleep()

unsigned int sleep(unsigned int seconds);

Çağıran iş parçacığının ya saniye cinsinden belirtilen gerçek zamanlı saniye sayısı geçene kadar ya da göz ardı edilmeyen bir sinyal gelene kadar uyumasına neden olur.

usleep()

int usleep(useconds_t usec);

Çağıran iş parçacığının yürütülmesini miskrosaniyesi boyunca askıya alır. 


ASCII karakterini Binary karaktere dönüştürün

ASCII tablosu, 127 ASCII karakterinin tamamını ve değerlerini temsil eder. Bu, her karakterin bir sayı ile temsil edildiği anlamına gelir.

İki programın sinyaller aracılığıyla iletişim kurmasının yolu ( SIGUSR1 ve SIGUSR2 ) her birinin ikili bir değeri temsil etmelerini sağlamaktır. Bu durumda SIGUSR1 0'ı temsil ettiğini ve SIGUSR2 1'i temsil ettiğini düşünüyoruz. Yani bir SIGUSR1sinyal gönderdiğimizde sunucuya 0 gönderiyoruz ve bir SIGUSR2sinyal göndererek 1 gönderiyoruz.

Bir karakterden tüm bitleri almaya odaklanmıştır - ASCII'de 8 bit - bu, sunucunun her ASCII karakteri için istemciden 8 sinyal alması gerektiği anlamına gelir.

>>>>>>>

a karakteri , ASCII tablosunda 97 sayısı ile temsil edilir.
İkili 97'de 01100001

(sağdan sola doğru değerler) 
2 üssü 0 + 0 + 0 + 0 + 0 + 2 üssü 5 + 2 üssü 6 + 0 = 97

Buradaki büyük soru, karakterin bitlerini tek tek nasıl elde edeceğimizdir.!
Bunları Bitwise Operators kullanarak alıyoruz.

SOL SHIFT (<<) operatörü, bitleri sola hareket ettirir, en soldaki biti atar ve en sağdaki bite 0 değerini atar.

0000 0001 << 1 = 0000 0010
0000 0001 < < 2 = 0000 0100

AND (&) operatörü iki biti karşılaştırır ve her iki bit de 1 ise 1 sonucunu üretir. Aksi takdirde 0 döndürür.

1100 0010 & 1000 0000 = 1000 0000 [167 & 128 == 128]

128 sayısını kullanarak, en soldaki bitte yalnızca 1 olan ve geri kalanı 0 [1000 0000] olan bir ikili sayı elde ederiz. 

#include <stdio.h>

void    print_bits(unsigned char octet)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		putchar((octet & 128) ? '1' : '0');
		octet <<= 1;
		bit++;
	}
	putchar('\n');
}

int main(int ac, char **av)
{
	int	i;
	char *word;
	
	i = 0;
	if (ac != 2)
		return (1);
	word = av[1];
	printf("Word = %s\n", word);
	while (word[i])
	{
		printf("%c[%d]:\t", word[i], word[i]);
		print_bits(word[i]);
		i++;
	}
	return (0);
}

>>>>>>>>>>

./a.out “EREN”

Word = EREN
E[69]:	10001010
R[82]:	10100100
E[69]:	10001010
N[78]:	10011100

getpid()

Çağıran işlemin işlem kimliğini (PID) döndürür.


pause()

Sinyal gelene kadar çalışır sinyal geldikten sonra kapanır. while(1) ile kullanırsak sürekli sinyal bekler alır yenisini bekler.



Not :  

gcc server.c -o server
./server

gcc client.c -o client
./clienti
