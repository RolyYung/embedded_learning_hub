#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define THREAD_NUM 3
#define QUEUE_SIZE 100

// --------------------
// 一份任务
// --------------------

typedef struct
{

  int id;
  char filename[100];

} Task;

// --------------------
// 任务队列
// --------------------

Task task_queue[QUEUE_SIZE];

int front = 0;
int rear = 0;
int task_count = 0;

// --------------------
// 同步工具
// --------------------

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

// --------------------
// worker
// --------------------

void *worker(void *arg)
{
  while (1)
  {

    // 准备访问公共任务队列
    pthread_mutex_lock(&mutex);

    // 没任务就睡觉
    while (task_count == 0)
    {

      pthread_cond_wait(
          &cond,
          &mutex);
    }

    // 取出队头任务
    Task task = task_queue[front];

    front = (front + 1) % QUEUE_SIZE;

    task_count--;

    // 公共队列操作结束
    pthread_mutex_unlock(&mutex);

    // --------------------
    // 真正执行任务
    // --------------------

    printf(
        "线程 %lu 开始处理任务%d：%s\n",
        pthread_self(),
        task.id,
        task.filename);

    sleep(2);

    printf(
        "线程 %lu 完成任务%d：%s\n",
        pthread_self(),
        task.id,
        task.filename);
  }

  return NULL;
}

// --------------------
// 提交任务
// --------------------

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

  printf(
      "[提交任务] %d：%s\n",
      id,
      filename);

  pthread_mutex_unlock(&mutex);

  // 告诉一个worker：
  // 来活了
  pthread_cond_signal(&cond);
}

// --------------------
// main
// --------------------

int main(void)
{
  pthread_t tids[THREAD_NUM];

  // 创建线程池里的3个worker
  for (int i = 0; i < THREAD_NUM; i++)
  {

    pthread_create(
        &tids[i],
        NULL,
        worker,
        NULL);
  }

  // 模拟用户提交图片处理任务

  submit_task(1, "cat.jpg");
  submit_task(2, "dog.jpg");
  submit_task(3, "car.jpg");
  submit_task(4, "tree.jpg");
  submit_task(5, "house.jpg");
  submit_task(6, "linux.jpg");
  submit_task(7, "ubuntu.jpg");
  submit_task(8, "penguin.jpg");

  // 教学版暂时不考虑线程池销毁
  for (int i = 0; i < THREAD_NUM; i++)
  {

    pthread_join(
        tids[i],
        NULL);
  }

  return 0;
}