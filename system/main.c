/*  main.c  - main */

#include <xinu.h>
#include <stdio.h>

sid32 sem;
pid32 wpid, spid;

void waiter(void), signaler(void);

int main(int argc, char **argv)
{
    sem = semcreate(20);
    resume(create(waiter, 1024, 40, "waiter", 0));
    resume(create(signaler, 1024, 40, "signaler", 0));

	return OK;
}

void waiter() {
    int32 i;
    for(i=1; i<=2000; i++) {
        kprintf("%d ", i);
        wait(sem);
    }
}


void signaler() {
    while(1) {
        int32 i;
        kprintf("signaler is running \n");
        for(i=1; i<=5; i++) {
            signal(sem);
        }
    }
}
