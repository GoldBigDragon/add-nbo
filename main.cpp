/*
  디지털포렌식트랙 김태룡
  2020.07.13. 06:42:31
*/
#include <string.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <netinet/in.h>

int main(int argc, char *argv[]){
  // 파라미터 수가 2개가 아닐 경우, 프로그램을 종료 시킵니다.
  if(argc != 3) {
    printf("[ ! ] Usage : %s <filename1> <filename2>\n", argv[0]);
    return 0;
  }
  // 파일 명을 127자 이상 적었을 경우, 프로그램을 종료시킵니다.
  if(strlen(argv[1]) > 127 || strlen(argv[2]) > 127){
    printf("[ x ] File name must less than 127!\n");
    return 0;
  }
 
  FILE *f1, *f2;
  uint8_t buffer1[4];
  uint8_t buffer2[4];
  
  // 0번째 파라미터는 명령문 그 자체이므로,
  // 1, 2번 파라미터를 불러옵니다.
  // 옵션으로 rb를 주어 binary 형식으로 읽도록 합니다.
  f1 = fopen(argv[1], "rb");
  f2 = fopen(argv[2], "rb");
  // 8비트 씩 끝까지 읽어들입니다.
  fread(buffer1,8,1,f1);
  fread(buffer2,8,1,f2);

  fclose(f1);
  fclose(f2);
  
  uint32_t *p1 = reinterpret_cast < uint32_t * > (buffer1);
  uint32_t *p2 = reinterpret_cast < uint32_t * > (buffer2);
  
  // ntohs 는 16비트, ntohl은 32비트이다!
  uint32_t n1 = ntohl(*p1);
  uint32_t n2 = ntohl(*p2);

  uint32_t n3 = n1 + n2;

  printf ("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", n1, n1, n2, n2, n3, n3);
  return 0;
}
