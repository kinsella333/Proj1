#include<stdio.h>
#include<string.h>
#include<sys/socket.h>
#include<arpa/inet.h>

int main(int argc , char *argv[])
{
    int sock;
    struct sockaddr_in server;
    char message[1024] , server_reply[1024];

    //Create socket
    sock = socket(AF_INET , SOCK_STREAM , 0);
    if (sock == -1)
    {
        perror("Could not create socket");
    }
    printf("Socket created\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);

    //Connect to remote server
    if (connect(sock ,(struct sockaddr *)&server , sizeof(server)) < 0){
        perror("connect failed. Error");
        return 1;
    }

    printf("Connected\n");

    //keep communicating with server
    do{
        printf("Enter message : ");
        scanf("%s" , message);

        //Send some data
        if(send(sock , message , strlen(message) , 0) < 0){
            perror("Send failed");
            return 1;
        }

        //Receive a reply from the server
        if(recv(sock , server_reply , sizeof(server_reply) , 0) < 0){
            perror("recv failed");
            break;
        }
        printf("%s\n",server_reply);
    }while(strcmp(message,"kill") != 0);

    close(sock);
    return 0;
}
