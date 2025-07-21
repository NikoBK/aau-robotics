/* NOTE:
* See the example file in: file > examples > krnl > k01myfirsttask, for documentation on all of this code.
*/
#include <krnl.h>

struct k_t *pTask; // pointer to task descriptor

#define STK 150

unsigned char taskStak1[STK];
unsigned char taskStak2[STK];
unsigned char taskStak3[STK];

void t1() {
  while (!Serial) ; // Wait for Serial

  while (1) {
    Serial.println("123456789012345678901234567890");
    k_sleep(500);
  }
}

void t2() {
  while (!Serial) ;

  while (1) {
    Serial.println("abcdefghijabcdefghijabcdefghij");
    k_sleep(500);
  }
}

void t3() {
  while (!Serial) ;

  while (1) {
    Serial.println("ABCDEFGHIJABCDEFGHIJABCDEFGHIJ");
    k_sleep(500);
  }
}

void(* resetFunc) (void) = 0;//declare reset function at address 0

void setup() {
  Serial.begin(115200);
  pinMode(13, OUTPUT);

  k_init(3, 0, 0); // 3 tasks, no queues or semaphores

  k_crt_task(t1, 5, taskStak1, STK);
  k_crt_task(t2, 5, taskStak2, STK);
  k_crt_task(t3, 5, taskStak3, STK);

  int res = k_start();
  if (res < 0) while (1); // Error fallback
}

void loop() {} // is NEVER used
