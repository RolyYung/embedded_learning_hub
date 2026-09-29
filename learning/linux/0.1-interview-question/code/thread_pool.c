#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define THREAD_NUM 3
#define QUEUE_SIZE 100

typedef struct
{
  int id;
  char filename[100];
} Task;

// 任务队列
Task task_queue[QUEUE_SIZE];

int front = 0;
int rear = 0;
int task_count = 0;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

void *worker(void *arg)
{
  while (1)
  {
    pthread_mutex_lock(&mutex);
    printf("worker task_count: %d \n", task_count);
    while (task_count == 0)
    {
      pthread_cond_wait(&cond, &mutex);
    }
    Task task = task_queue[front];
    front = (front + 1) % QUEUE_SIZE;
    task_count--;

    pthread_mutex_unlock(&mutex);

    printf(
        "线程开始处理任务%d：%s\n",
        task.id,
        task.filename);
    printf("sleep begin \n");
    sleep(2);
    printf("sleep end \n");
    printf(
        "线程完成任务%d：%s\n",
        task.id,
        task.filename);
  }
  return NULL;
}

void submit_task(int id, const char *filename)
{
  pthread_mutex_lock(&mutex);
  task_queue[rear].id = id;
  snprintf(
      task_queue[rear].filename,
      sizeof(task_queue[rear].filename),
      "%s",
      filename);
  rear = (rear + 1) % QUEUE_SIZE;
  task_count++;
  pthread_mutex_unlock(&mutex);

  pthread_cond_signal(&cond);
  return;
}

int main(void)
{
  printf("AAAA \n");
  pthread_t tids[THREAD_NUM];

  for (int i = 0; i < 3; i++)
  {
    int ret = 0;
    ret = pthread_create(&tids[i], NULL, worker, NULL);
    printf("ret value: %d \n", ret);
  }

  submit_task(1, "cat.jpg");
  submit_task(2, "dog.jpg");
  submit_task(3, "car.jpg");
  submit_task(4, "tree.jpg");
  submit_task(5, "house.jpg");
  submit_task(6, "linux.jpg");
  submit_task(7, "ubuntu.jpg");
  submit_task(8, "penguin.jpg");

  for (int i = 0; i < THREAD_NUM; i++)
  {
    pthread_join(
        tids[i],
        NULL);
  }

  return 0;
}