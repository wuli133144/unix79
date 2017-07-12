#include"../inc/common.h"
#include<pthread.h>


/*@Fork start@*/
 pid_t Fork(){
    pid_t pid;
    if((pid=fork())<0){
        err_dump("fork");
    }
   return pid;
 }


/*@fork end@*/


/*@pthread_create start@*/
int Pthread_create(pthread_t *  pid,
                   const pthread_attr_t * attr,
                   void *(*hand)(void *),
                   void * para){
       int ret;
       if((ret=pthread_create(pid,attr,hand,para))!=0){
           err_dump("pthread_create");
       }
       return ret;
}
/*@pthread_create end@*/


////////////////测试函数栈大小//////////////////////

int i=0;
#define BZ  256 
void add(){
    int buf[BZ];
    printf("i=%d\n",i++);
    add();
}
/////////////////////////////////////////////////


void *pthread_worker(void *para){
      int tid=syscall(SYS_gettid);
      printf("pthread_%id ,%id\n",tid,tid);
      printf("pthread_self()%d\n",pthread_self());
      printf("pthread_%d exiting...\n",tid);
      pthread_exit(NULL);
      return NULL;
}


/*@pthread_attr_setstacksize() start@*/
int Pthread_attr_setstacksize(pthread_attr_t *attr,size_t stacksize){
      int ret;
      if((ret=pthread_attr_setstacksize(attr,stacksize))!=0){
          err_dump("setstacksize");
      }
      return ret;
}
/*@pthread_attr_setstacksize end@*/

/*@pthread_attr_getstacksize stack@*/
  int Pthread_attr_getstacksize(pthread_attr_t *attr,size_t *stacksize){
        int ret;
        if((ret=pthread_attr_getstacksize(attr,stacksize))!=0){
            err_dump("pthread_attr_getstacksize()!");
        }
        return ret;
  }
/*@pthread_attr_getstacksize end@*/
/*@test pthread_hand start @@*/
void *pthread_hand(void *para){

       printf("pthread_id=%d",pthread_self());
       pthread_attr_t attr;
       size_t sz;
       pthread_attr_init(&attr);//init pthread_attr
       Pthread_attr_getstacksize(&attr,&sz);
       printf("pthread_size=%d\n",sz);
       return NULL;
}

/*@pthread_hand end@*/

/*@test pthread_exit exit return@*/

void* pthread_test1(void *para){
    
   // printf("pthread_test1() \n");
 //   pthread_exit(NULL);//end all pthread
    int pa= (int)*para;
    pthread_join(pa,NULL);

    return ;
}

void pthread_test2(void *para){
     // printf("pthread_test1() \n");
    //   pthread_exit(NULL);//end all pthread
    int pa= (int)*para;
    pthread_join(pa,NULL);
    return ;
}

void *pthread_test(void *para){
         pthread_test1();  
         printf("pthread_test()\n");
         return ;

}

/*@test pthread_exit exit return@*/

/*@set pthread_attr_stedetachstate@*/
  int Pthread_attr_setdetachstate(pthread_attr_t *attr,int detachstat){
            int ret;
            if((ret=Pthread_attr_setdetachstate(attr,detachstat))!=0){
                err_dump("pthread_attr_setdetachstate!");
            }
            return ret;
  }
/*@pthread_attr_stedetachstate@*/



/*@get pthread_attr_stedetachstate@*/
  int Pthread_attr_getdetachstate(pthread_attr_t *attr,int *detachstat){
            int ret;
            if((ret=Pthread_attr_getdetachstate(attr,detachstat))!=0){
                err_dump("pthread_attr_setdetachstate!");
            }
            return ret;
  }
/*@pthread_attr_getdetachstate@*/



int main(){


   #if 1
     pthread_t pid[2];
     Pthread_create(&pid[0],NULL,pthread_test1,(void *)&pid[1]);
     Pthread_create(&pid[1],NULL,pthread_test1,(void *)&pid[0]);
     
    
     
   #endif


    #if 0
        pthread_t pid;
        Pthread_create(&pid,NULL,pthread_test,NULL);
        pthread_join(pid,NULL);

    #endif 
    #if 0 
      
                pthread_t pid;
                pthread_attr_t attr;
                pthread_attr_init(&attr);
                Pthread_attr_setstacksize(attr,10200);
                int i;
                Pthread_create(&pid,&attr,pthread_hand,NULL);
                pthread_join(pid,NULL);
        
        return 0;
    #endif
    
    #if 0
      pthread_t pid[2];
       
     int i;
        for(i=0;i<2;i++){
            Pthread_create(&pid[i],NULL,pthread_worker,NULL);
        }
        for(i=0;i<2;i++){
           pthread_join(pid[i],NULL);
        }


      #endif

    #if 0
    int i=0;
    pid_t pid;

    for(i=0;i<10000;i++){
       if(!(pid=Fork())){
           exit(0);
       }
    }
    
    waitpid(0,&i,-1);

    return 0;

    #endif 


    #if 0
     
     pthread_t pid[0];
     
     int i;
     for(i=0;i<3;i++){
         pthreadf_create(&pid[i],NULL,pthread_hand,NULL);
     }

    
    for(i=0;i<3;i++){
        pthread_join(pid[i],NULL);
    }

    #endif

    #if 0
    add();
    
    #endif
    
    #if 0
     pthread_t pid[2];
     for(int i=0;i<2;i++){
         Pthread_create(&pid[i],NULL,pthread_hand,NULL);
     }

     for(int i=0;i<2;i++){
         pthread_join(pid[i],NULL);
     }

    #endif

   #if 1
   #endif 

}