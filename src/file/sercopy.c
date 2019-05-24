erName);
			printf("--��(� -send <%s> to <%s> successfully!\n", info, conn[i].UserName);
		}	
	return 0;	
}



//this function sends the file of single client to the others
//File is the filename needed to be sent
int SendFile(char* Filename, void* clientStruct)
{
	char*filename = Filename;
	int size;
	int filesize;
	char buffer[1024];
	int len;
	connection_t* clientInfo = (connection_t *)clientStruct;	
	read(clientInfo->sock, &size, sizeof(int));
        read(clientInfo->sock, &filesize, sizeof(int));
	for(int i=0; i < filesize/1024+1; ++i)
	{
		read(clientInfo->sock, &len, sizeof(int));
		read(clientInfo->sock, buffer, len);
		SendInfo(buffer);
	}	
	return 0;
}
//This function deals with single client, aim to receive message from this client
//and then send them to another using SendInfo
void* Receive(void* clientStruct)
{

	connection_t* clientInfo = (connection_t *)clientStruct;
	while(1)
	{
		//read the message from the client
		char *Buffer;
		int messageLen = 0;
		read(clientInfo->sock, &mes��(� sageLen, sizeof(int));
		if(messageLen > 0)
		{
			Buffer = (char *)malloc((messageLen+1)*sizeof(char));
			read(clientInfo->sock, Buffer, messageLen);   // the program stucks here and don't know why
						
			if(Buffer[0] != ':') continue;
			Buffer[messageLen] = '\0';
			//whether the client want to quit
			if( Buffer[1] == 'q' && Buffer[2] == '!' )
			{
				//constitute quit message and delete this client
				char quit[] = " quit the chat room\n";
				char quitMessage[50];		
				char quitNumber[50];
				quitMessage[0] = '\0';
				sprintf(quitNumber, "There are %d people in the Chatroom now!!\n", --clientNumber);
				strcat(quitMessage, clientInfo->UserName);
				strcat(quitMessage, quit);	
				strcat(quitMessage, quitNumber);
				//send the info to the others
				SendInfo(quitMessage);
				clientInfo->addr_len = -1;
				pthread_exit(&clientInfo->threadNumber);
			}
			else if ( Buffer[1] == 'f' && Buffer[2]  =='!')
			{	
				//send the file to the others
				char sign[] = "!!";��(� 
                                char file[] = " send you a file named as ";
				char fileMessage[50];
				char Filename[FILE_NAME_MAX_SIZE];
				fileMessage[0] = '\0';
				strcat(fileMessage, clientInfo->UserName);
				strcat(fileMessage, file);
				//read the file name  from buffer
				//send the file to the others
				for(int t = 3; t < messageLen-2; t++)
					Filename[t-3] = Buffer[t];
				Filename[messageLen-5]='\0';
				strcat(fileMessage, Filename);
				strcat(sign, fileMessage);
				SendInfo(sign);
				printf("%s\n", Filename);
				SendFile(Filename, clientInfo);
			}
			else{
				//constitute the message
				char begin[] = " says";
				char messageDistribute[200];
				messageDistribute[0] = '\0';
				strcat(messageDistribute, clientInfo->UserName);
				strcat(messageDistribute, begin);
				strcat(messageDistribute, Buffer);
				SendInfo(messageDistribute);
			}
			free(Buffer);
		}
		else
			continue;
	}
}

//determine whether userName already exist
//return 1 if ex��(� isted, otherwise 0
int usernameExisted(char userName[], int clientnumber)
{
	for(int i = 0; i < 100 && i != clientnumber; ++i)
	{
		if(conn[i].addr_len != 0 && conn[i].addr_len != -1)
			if(strcmp(conn[i].UserName, userName) == 0)
				return 1;

	}	
	return 0;
}


//aim to accept whenever there is a client trying to connect
void * process(void * ptr)
{
	pthread_t clientThread[100];
	char * buffer;
	int len;
	//the number of the client connecting now
	clientNumber = 0;      
	long addr = 0;
	while(1){
		//waiting to be connected
		if(clientNumber < 100)
		{
			conn[clientNumber].sock = accept(ServerSock, &conn[clientNumber].address, &conn[clientNumber].addr_len);
		}
		else
			break;


		//the length of the message
		read(conn[clientNumber].sock, &len, sizeof(int));
		if (len > 0)
		{

			//multiple information of a client
			addr = (long)((struct sockaddr_in *)&conn[clientNumber].address)->sin_addr.s_addr;
			buffer = (