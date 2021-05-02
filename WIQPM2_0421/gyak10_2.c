#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/msg.h>
#define MSGKEY 654321L

struct msgbuf1 {
	long mtype;
	char mtext[512];
} rcvbuf, sndbuf, *msgp;

struct msqid_ds ds, *buf;

int main()
{
    pid_t child;
    if((child=fork()) < 0) {
        perror("fork");
        return 1;
    }


    if (child == 0) {
        int msgid;
        key_t key;
        int msgflg;
        int rtn, msgsz;

        key = MSGKEY;
        msgflg = 00666 | IPC_CREAT;
        msgid = msgget( key, msgflg);
        if ( msgid == -1) {
                    perror("\n The msgget system call failed!");
                    exit(-1);
            }
        printf("\n Az msgid %d, %x : ", msgid,msgid);

        msgp        = &sndbuf;
        msgp->mtype = 1;
        strcpy(msgp->mtext,"Egyik uzenet");
        msgsz       = strlen(msgp->mtext) + 1;

        rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
        printf("\n Az 1. msgsnd visszaadott %d-t", rtn);
        printf("\n A kikuldott uzenet:%s", msgp->mtext);

        strcpy(msgp->mtext,"Masik uzenet");
        msgsz       = strlen(msgp->mtext) + 1;
        rtn = msgsnd(msgid,(struct msgbuf *) msgp, msgsz, msgflg);
        printf("\n A 2.  msgsnd visszaadott %d-t", rtn);
        printf("\n A kikuldott uzenet:%s", msgp->mtext);
        printf("\n");

        exit (0);
    }
    else if (child > 0) {
        int returnStatus;
        waitpid(child, &returnStatus, 0);
        int msgid;
        key_t key;
        int mtype, msgflg;
        int rtn, msgsz;

        key = MSGKEY;
        msgflg = 00666 | IPC_CREAT | MSG_NOERROR;

        msgid = msgget( key, msgflg);
        if ( msgid == -1) {
                    perror("\n The msgget system call failed!");
                    exit(-1);
            }
        printf("\n Az msgid: %d",msgid);

        msgp = &rcvbuf;
        buf = &ds;
        msgsz = 20;
        mtype = 0;
        rtn = msgctl(msgid,IPC_STAT,buf);
        printf("\n Az uzenetek szama: %d",buf->msg_qnum);
    }
}
