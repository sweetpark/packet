#include <stdio.h>
#include <string.h>
#include <memory.h>


int main(void){
    FILE *fp,*fp1;
    char file_buff[10000];
    char test_buff[10000];

    fp = fopen("hex_value","r");
    fp1 = fopen("test_write.txt","w");
    char *search = "FF D8 FF E0";
    char *remove_search="FF D9";
    char *result;
    char *remove;
    int lp; // 파일포인터 위치 찾기

    if(fp==NULL){
        printf("파일 열기 실패!\n");
    }else{
        printf("파일 열기 성공!\n");
    }

    if(fp1==NULL){
        printf("파일 열기 실패!\n");
    }else{
        printf("파일 열기 성공!\n");
    }
    

    while(fgets(file_buff,sizeof(file_buff),fp) != NULL){
        printf("%s",file_buff);
        //memset(file_buff,0,sizeof(file_buff)); //메모리 초기화 file_buff의 내용값을 초기화시킴
        //memset은 메모리를 초기화하거나, 문자를 바꿀 때 사용
        result = strstr(file_buff,search);
        remove = strstr(result,remove_search);
    
        if(remove != NULL){
            fwrite(result,strlen(result),1,fp1);
            lp = strlen(result)-(remove-result)+1;
            fseek(fp1,(-1)*lp,SEEK_CUR);//현재 위치 = 파일 끝지점 , lp는 파일포인터 위치 변경 , -값은 끝에서부터 반대로 줄여가는 것
            fwrite(" ",strlen(remove),1,fp1); //remove 크기만큼 1번 공백으로 채워넣음
            //fseek(fp1,lp -4,SEEK_CUR);
            fseek(fp1,-1L,SEEK_END);
            fwrite(remove_search,strlen(remove_search),1,fp1);
        }
        printf("%s\n",result);
    }

    memset(file_buff,0,sizeof(file_buff));
    /*
    //파일에저장후 원하는 페이로드값 가져오기
    result = strstr(file_buff,search);
    remove = strstr(result,remove_search);

    if(remove != NULL){
        fwrite(result,strlen(result),1,fp1);
        lp = strlen(result)-(remove-result)+1;
        fseek(fp1,(-1)*lp,SEEK_CUR);
        fwrite(" ",strlen(remove),1,fp1);
        fseek(fp1,lp -4,SEEK_CUR);
    } 


*/
    
    //printf("%s\n",result);

    fclose(fp);
    fclose(fp1);
    return 0;
}