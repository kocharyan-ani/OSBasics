#include <Windows.h>
#include <stdio.h>
#include <tchar.h>

const int MAX_ITEMS_FOR_PRODUCER = 50;
const int MAX_ITEMS_FOR_CONSUMER = 50;
const int PRODUCER_QTY = 5;
const int CONSUMER_QTY = 5;
const int BUFFER_SIZE = 80;

HANDLE empty, full, mutex;
int buffer[BUFFER_SIZE];
int in = 0, out = 0;

void error_text_output() {}

DWORD producer(void* p) {
    const int producer_number = *static_cast<int*>(p);
    int item{};
    for (int i = 0; i < MAX_ITEMS_FOR_PRODUCER; ++i) {
        item = rand();
        WaitForSingleObject(empty, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        buffer[in] = item;
        _tprintf(_T("Producer %d: Insert Item %d at %d\n"), producer_number, buffer[in], in);
        in = (in + 1) % BUFFER_SIZE;
        ReleaseMutex(mutex);
        ReleaseSemaphore(full, 1, NULL);
    }
    delete p;
	return 0;
}

DWORD consumer(void* p) {
    const int consumer_number = *static_cast<int*>(p);
    for (int i = 0; i < MAX_ITEMS_FOR_CONSUMER; ++i) {
        WaitForSingleObject(full, INFINITE);
        WaitForSingleObject(mutex, INFINITE);
        int item = buffer[out];
        _tprintf(_T("Consumer %d: Remove Item %d from %d\n"), consumer_number, item, out);
        out = (out + 1) % BUFFER_SIZE;
        ReleaseMutex(mutex);
        ReleaseSemaphore(empty, 1, NULL);
    }
    delete p;
	return 0;
}

int _tmain() {
    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);
    mutex = CreateMutex(NULL, FALSE, NULL);
    if (NULL == empty || NULL == full || NULL == mutex) {
        error_text_output();
        return 1;
    }

    HANDLE producers[PRODUCER_QTY]{};
    for (int i = 0; i < PRODUCER_QTY; ++i) {
        producers[i] = CreateThread(NULL, 0, producer, new int(i), 0, NULL);
        if (NULL == producers[i]) {
            error_text_output();
            return 1;
        }
    }

    HANDLE consumers[CONSUMER_QTY]{};
    for (int i = 0; i < CONSUMER_QTY; ++i) {
        consumers[i] = CreateThread(NULL, 0, consumer, new int(i), 0, NULL);
        if (NULL == consumers[i]) {
            error_text_output();
            return 1;
        }
    }

    if (WAIT_FAILED == WaitForMultipleObjects(PRODUCER_QTY, producers, TRUE, INFINITE)) {
        error_text_output();
        return 1;
    }
    if (WAIT_FAILED == WaitForMultipleObjects(CONSUMER_QTY, consumers, TRUE, INFINITE)) {
        error_text_output();
        return 1;
    }

    for (int i = 0; i < PRODUCER_QTY; ++i) {
        CloseHandle(producers[i]);
    }
    for (int i = 0; i < CONSUMER_QTY; ++i) {
        CloseHandle(consumers[i]);
    }
    CloseHandle(mutex);
    CloseHandle(empty);
    CloseHandle(full);

    return 0;
}