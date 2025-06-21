# 🧠 Philosophers

![Image](https://github.com/user-attachments/assets/fa6687d2-a8ee-4ea1-a266-c27e592b7e4a)

## 📌 Overview

**Philosophers** is one of the foundational concurrency projects at **42 Network**, designed to teach you how to avoid **race conditions**, **deadlocks**, and **starvation** through controlled use of **threads**, **mutexes**, **processes**, and **semaphores**.

Inspired by the classic *Dining Philosophers Problem*, this project simulates philosophers who alternate between thinking, eating, and sleeping — while competing for access to limited shared forks.

---

## ✨ Features

### 🧵 Mandatory Part (Threads & Mutexes)

* 🧠 Multithreading with `pthread`
* 🔐 Mutex locks to manage fork access
* 🕓 Accurate timing and life tracking
* ❌ Deadlock avoidance strategy
* 💀 Death detection monitor per philosopher
* 🍝 All philosophers eat and sleep without starvation

### 🧪 Bonus Part (Processes & Semaphores)

* 🧬 Each philosopher is a separate process
* 🔁 Global semaphores to manage forks and writing
* 🧵 Thread used **only** to monitor death per philosopher
* 🚨 Semaphore-based death detection and cleanup
* 🔒 Fork synchronization using semaphores
* 🧼 Clean exit and process termination on death

---

## 🗂️ Project Structure

| Part      | Model     | Tools Used                            |
| --------- | --------- | ------------------------------------- |
| Mandatory | Threads   | `pthread`, `mutex`                    |
| Bonus     | Processes | `fork`, `sem_open`, `waitpid`, `kill` |

---

## 🔍 How It Works

Each philosopher follows this cycle:

```
Think 🤔 → Take forks 🍴 → Eat 🍝 → Sleep 😴 → Repeat
```

They must take **two forks** to eat — but each fork is a **shared resource**:

* In the **thread version**, forks are protected using `pthread_mutex_t`
* In the **process version**, forks are counted and synchronized using `sem_t`

---

## 🧠 Key Concepts

### 💥 Deadlock Prevention

* Even-indexed philosophers delay their start to avoid circular waits.
* Mutexes/semaphores ensure no two philosophers access the same fork simultaneously.

### 💀 Death Monitoring

* A thread/process checks if a philosopher hasn’t eaten within `time_to_die`
* If so, it prints a death message and ends the simulation

### 🕰️ Timing Accuracy

* Millisecond-precision sleep and timestamps
* Avoid busy-waiting and drift using custom `usleep` functions

---

## 🛠️ Technical Constraints

* ✅ No data races
* ❌ No use of busy waiting (spinlocks)
* ✅ Thread-safe stdout printing
* 🧹 No memory leaks or zombie processes
* 📜 42 Norminette compliant:

  * Max 25 lines per function
  * Max 4 variables per function
  * Max 4 arguments per function

---

## ▶️ How to Compile and Run

### 🔧 Compile

- For mandatory (threads version)
```bash
cd philo
make
```

- For bonus (processes version)
```bash
cd philo_bonus
make
```

### 🚀 Run

```bash
./philo 5 800 200 200
```

Arguments:

```bash
./philo number_of_philos time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```

---

## 🧪 Example Outputs

### ✅ Normal run

```
0 1 has taken a fork
0 1 has taken a fork
0 1 is eating
200 1 is sleeping
400 1 is thinking
```

### 💀 Philosopher dies

```
800 3 died
```
