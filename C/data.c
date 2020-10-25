#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>

#define HET 229461668171625
#define KED 6385399549
#define SZE 6954038150926
#define CSU 14972738393202911825
#define PEN 229471999720499
#define SZO 229483270658021
#define VAS 249910433795945188

const unsigned long hash(const char *str)
{
  unsigned long hash = 5381;
  int c;
  while ((c = *str++))
    hash = ((hash << 5) + hash) + c;
  return hash;
}
int rand_comparison(const void *a, const void *b)
{
    (void)a; (void)b;

    return rand() % 2 ? +1 : -1;
}

void shuffle(void *base, size_t nmemb, size_t size)
{
    qsort(base, nmemb, size, rand_comparison);
}

void handler(int signumber,siginfo_t* info,void* nonused){
  printf("\nA járatvezetőtől az infó megérkezett: %d ember dolgozik!\n",info->si_value.sival_int);
  } 


void options();
// open(P) is a standard Posix function
void new_worker();
void max_worker_per_day();
void print_day();
void print_everything();
void delete_worker();
void modify_worker();
void read_all_data();
void second_task();
// exit(3) is a standard C function
void pexit();

struct Worker
{
  char _name[20];
  char _address[50];
  // int _days[15];
};

struct Worker *workers[7][20];
int max_workers_per_day[7] = {1, 1, 1, 1, 1, 1, 1};

void init_worker(struct Worker *w)
{
  for (int i = 0; i < 20; i++)
  {
    w->_name[i] = ' ';
  }

  for (int i = 0; i < 50; i++)
  {
    w->_address[i] = ' ';
  }

  // for ( int i = 0; i < 15; i++)
  // {
  //     w->_days[i] = -1;
  // }
}

void printWorker(struct Worker *w)
{
  printf("Name : %s\n", w->_name);
  printf("Address : %s\n", w->_address);
  //  for (int i = 0; i < 15; i++)
  //  {
  //      if (w->_days[i]!= -1){
  //          printf("%d", w->_days[i]);
  //      }
  //  }
}

int main(void)
{

  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      workers[i][j] = NULL;
    }
  }
  char option;
  read_all_data();

  while (1)
  {
    printf("****Jó bor, jó egészség szőlészet****\n");
    printf("Válasszon 1-8 között: \n");
    options();
    option = getc(stdin);
    // swallow the '\n'
    getc(stdin);
    switch (option)
    {
    case '1':
      new_worker();
      break;
    case '2':
      max_worker_per_day();
      break;
    case '3':
      print_day();
      break;
    case '4':
      print_everything();
      break;
    case '5':
      delete_worker();
      break;
    case '6':
      modify_worker();
      break;
    case '7':
      second_task();
    case '8':
      pexit();
    default:
      pexit();
    }
  }
  return 0;
}

void options()
{
  puts("1. Új munkás hozzáadása");       //finish me
  puts("2. Maximális munkások naponta"); //fix me
  puts("3. Napi lista készítése");
  puts("4. Teljes lista készítése");
  puts("5. Dolgozó törlése");
  puts("6. Dolgozó adatainak módosítása");
  puts("7. Második beadandó");
  puts("8. Exit");
}

void put_worker_in_day(int d, struct Worker *w)
{
  int number_of_workers = 0;
  for (int i = 0; i < 20; i++)
  {
    if (workers[d][i] != NULL)
      number_of_workers++;
  }
  if (number_of_workers >= max_workers_per_day[d])
  {
    printf("Unsuccessful: ");
    return;
  }

  for (int i = 0; i < 20; i++)
  {
    if (workers[d][i] == NULL)
    {
      workers[d][i] = w;
      printf("Successful: ");
      return;
    }
  }
}

void new_worker()
{

  struct Worker *W = malloc(70 * sizeof(int) + 15 * sizeof(char));
  init_worker(W);

  char n[20];

  puts("Név:");
  scanf("%[^\n]%*c", n);
  strcpy(W->_name, n);

  char h[50];

  puts("Cím:");
  scanf("%[^\n]%*c", h);
  strcpy(W->_address, h);

  char d[50];

  puts("Napok:");
  scanf("%[^\n]%*c", d);

  char *pch;
  pch = strtok(d, " ");

  while (pch != NULL)
  {
    switch (hash(pch))
    {
    case HET:
      put_worker_in_day(0, W);
      printf("Hétfő\n");
      break;
    case KED:
      put_worker_in_day(1, W);
      printf("Kedd\n");
      break;
    case SZE:
      put_worker_in_day(2, W);
      printf("Szerda\n");
      break;
    case CSU:
      put_worker_in_day(3, W);
      printf("Csütörtök\n");
      break;
    case PEN:
      put_worker_in_day(4, W);
      printf("Péntek\n");
      break;
    case SZO:
      put_worker_in_day(5, W);
      printf("Szombat\n");
      break;
    case VAS:
      put_worker_in_day(6, W);
      printf("Vasárnap\n");
      break;
    }
    pch = strtok(NULL, " ");
  }

  printWorker(W);
}

void max_worker_per_day()
{
  int i;
  printf("Hétfő:");
  scanf("%d", &i);
  max_workers_per_day[0] = i;
  printf("Kedd:");
  scanf("%d", &i);
  max_workers_per_day[1] = i;
  printf("Szerda:");
  scanf("%d", &i);
  max_workers_per_day[2] = i;
  printf("Csütörtök:");
  scanf("%d", &i);
  max_workers_per_day[3] = i;
  printf("Péntek:");
  scanf("%d", &i);
  max_workers_per_day[4] = i;
  printf("Szombat:");
  scanf("%d", &i);
  max_workers_per_day[5] = i;
  printf("Vasárnap:");
  scanf("%d", &i);
  max_workers_per_day[6] = i;

  for (int i = 0; i < 7; i++)
  {
    printf("%d. napon %d max ember\n", i, max_workers_per_day[i]);
  }
  getc(stdin);
}

void print_day()
{
  puts("Melyik napot szeretné?");
  puts("1. Hétfő");
  puts("2. Kedd");
  puts("3. Szerda");
  puts("4. Csütörtök");
  puts("5. Péntek");
  puts("6. Szombat");
  puts("7. Vasárnap");

  int c;
  scanf("%d", &c);
  int corr_num = c - 1;
  printf("%d a nap", corr_num);
  for (int i = 0; i < 20; i++)
  {
    if (workers[corr_num][i] != NULL)
    {
      printWorker(workers[corr_num][i]);
    }
  }
  getc(stdin);
}

void print_everything()
{
  for (int i = 0; i < 7; i++)
  {
    printf("\n\n%d. nap\n\n", i);
    for (int j = 0; j < 20; j++)
    {
      if (workers[i][j] != NULL)
      {
        printWorker(workers[i][j]);
      };
    }
  }
}

void delete_worker()
{
  char n[20];
  puts("Törlendő dolgozó neve: ");
  scanf("%[^\n]%*c", n);
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      if (workers[i][j] != NULL)
      {
        if (strcmp(n, workers[i][j]->_name) == 0)
        {
          workers[i][j] = NULL;
          printf("Adat sikeresen törölve.\n");
        }
      }
    }
  }
}

void modify_worker()
{
  char n[20];
  char nn[20];
  puts("Módosítandó dolgozó neve: ");
  scanf("%[^\n]%*c", n);
  struct Worker *w = NULL;
  for (int i = 0; i < 7; i++)
  {
    for (int j = 0; j < 20; j++)
    {
      if (workers[i][j] != NULL)
      {
        if (strcmp(n, workers[i][j]->_name) == 0)
        {
          printWorker(workers[i][j]);
          w = workers[i][j];
          printf("\nDolgozó megtalálva!\n");
          goto done;
        }
      }
    }
  }
done:
  puts("Új név:");
  scanf("%[^\n]%*c", nn);
  strcpy(w->_name, nn);

  char h[50];

  puts("Új cím:");
  scanf("%[^\n]%*c", h);
  strcpy(w->_address, h);
  printf("Az új adatok:\n");
  printWorker(w);
}

void read_all_data()
{
  FILE *infile;

  infile = fopen("workers.dat", "r");
  if (infile == NULL)
  {
    fprintf(stderr, "\nError opend file\n");
    exit(1);
  }

  for (int i = 0; i < 7; i++)
  {
    int number_of_workers = 0;

    fread(&number_of_workers, sizeof(int), 1, infile);

    for (int j = 0; j < number_of_workers; j++)
    {
      workers[i][j] = malloc(sizeof(struct Worker));
      fread(workers[i][j], sizeof(struct Worker), 1, infile);
    }

    for (int j = number_of_workers; j < 20; j++)
    {
      workers[i][j] = NULL;
    }
  }

  fread(&max_workers_per_day, sizeof(int), 7, infile);

  fclose(infile);
}

void second_task()
{

  int fd[2];
  srand(time(NULL));
  char msg[200];
  pipe(fd);
  int nap;
  char *works[] = {"metszes", "rugyfakaszto permet", "tavaszi nyitas", "horolas"};
  char *work_place[] = {"Jeno telek", "Lovas dulo", "Hosszu", "Selyem telek", "Malom telek", "Szula"};
  char *backupworkers[] = {"Andras",
                           "Zoltan",
                           "Peter",
                           "Kinga",
                           "Emese",
                           "Tamas"};
  int status;

  pid_t child = fork(); //forks make a copy of variables
  if (child < 0)
  {
    perror("The fork calling was not succesful\n");
    exit(1);
  }
  if (child > 0) //the parent process, it can see the returning value of fork - the child variable!
  {
    puts("Melyik napot szeretné?");
    puts("1. Hétfő");
    puts("2. Kedd");
    puts("3. Szerda");
    puts("4. Csütörtök");
    puts("5. Péntek");
    puts("6. Szombat");
    puts("7. Vasárnap");

    int c;
    scanf("%d", &c);
    nap = c - 1;
    printf("%d a nap\n\n", nap);

    waitpid(child, &status, 0);

    close(fd[1]);

    read(fd[0], msg, sizeof(msg));
    printf("%s", msg);

    char pipename[20];
    sprintf(pipename, "/tmp/%d", getpid());
    int fid = mkfifo(pipename, S_IRUSR | S_IWUSR);

    pid_t second_child = fork();
    int fd;

    if (second_child > 0)
    { //parent
       struct sigaction sigact;
      
      sigact.sa_sigaction=handler; //instead of sa_handler, we use the 3 parameter version
      sigemptyset(&sigact.sa_mask); 
      sigact.sa_flags=SA_SIGINFO; //we need to set the siginfo flag 
      sigaction(SIGTERM,&sigact,NULL); 
      int workers_in_that_day = 0;
      for (int i = 0; i < 20; i++)
      {
        if (workers[nap][i] != NULL)
        {
          workers_in_that_day++;
        }
      }
      fd = open(pipename, O_WRONLY);
      write(fd, &workers_in_that_day, sizeof(int));
      for (int i = 0; i < 20; i++)
      {
        if (workers[nap][i] != NULL)
        {
          write(fd, workers[nap][i]->_name, 20);
        }
      }
      write(fd, msg, sizeof(msg));
      close(fd);
      //wait(second_child);
      pause();
    }
    else
    {
      int darab;
      fd=open(pipename, O_RDONLY);
      read(fd, &darab, sizeof(int));
      printf("Ennyit olvastam a csőből: %d\n", darab);

      char dolgozo[20];
      for (int i = 0; i < darab; i++)
      {
        read(fd, dolgozo, 20);
        printf("Átküldött dolgozó neve: %s\n", dolgozo);
      }
      char hely[200];
      
      read(fd, hely, sizeof(hely));
      printf("Hely és munka: %s\n", hely);
      close(fd);
      unlink(pipename);

      int szukseges_keret = rand() % 6 + 1;
      printf("szukseges keret: %d\n", szukseges_keret);

      if (darab < szukseges_keret){
        int kulomb = szukseges_keret - darab;
        shuffle(backupworkers, 6, sizeof(char*));
        for (int i = 0; i < kulomb; i++)
        {
          printf("véletlen dolgozó: %s\n", backupworkers[i]);
        }
      }
      
      union sigval message;
      message.sival_int = szukseges_keret;
      sigqueue(getppid(), SIGTERM, message);



    }
  }
  else //child process
  {
    int randomplace = rand() % (sizeof(work_place) / sizeof(work_place[0]));
    int randomwork = rand() % (sizeof(works) / sizeof(works[0]));
    char *place = work_place[randomplace];
    char *work = works[randomwork];
    close(fd[0]);

    write(fd[1], place, strlen(place));
    write(fd[1], ", ", 2);
    write(fd[1], work, strlen(work) + 1);
    close(fd[1]);
    puts("kesz gyerek");
    exit(0);
  }
}

void pexit()
{
  FILE *outfile;

  outfile = fopen("workers.dat", "w");
  if (outfile == NULL)
  {
    fprintf(stderr, "\nError opend file\n");
    exit(1);
  }

  for (int i = 0; i < 7; i++)
  {
    int number_of_workers = 0;
    for (int j = 0; j < 20; j++)
    {
      if (workers[i][j] != NULL)
      {
        number_of_workers++;
      }
    }
    fwrite(&number_of_workers, sizeof(int), 1, outfile);
    for (int j = 0; j < 20; j++)
    {
      if (workers[i][j] != NULL)
      {
        fwrite(workers[i][j], sizeof(struct Worker), 1, outfile);
      }
    }
  }

  fwrite(&max_workers_per_day, sizeof(int), 7, outfile);

  fclose(outfile);

  puts("Képzeld el, hogy az összes adatodat egy biztonságos helyre mentettem!");
  exit(EXIT_SUCCESS);
}
