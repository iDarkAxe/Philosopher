# Dining philosophers Problem #

## <a name="introduction-en">📖 Introduction ##

Own implementation of the 'Dining philosophers problem', originally formulated in 1965 by Edsger Dijkstra as a student exam exercise.
Soon after, Tony Hoare gave the problem its present form.

See the link for more informations:
[📖 Dining philosophers problem](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### Requirements ###

* One or more philosophers sit at a round table.
There is a large bowl of spaghetti in the middle of the table.
* The philosophers alternatively eat, think, or sleep.
While they are eating, they are not thinking nor sleeping;
while thinking, they are not eating nor sleeping;
and, of course, while sleeping, they are not eating nor thinking.
* There are also forks on the table. There are as many forks as philosophers.
* Because serving and eating spaghetti with only one fork is very inconvenient, a
philosopher takes their right and their left forks to eat, one in each hand.
* When a philosopher has finished eating, they put their forks back on the table and
start sleeping. Once awake, they start thinking again. The simulation stops when
*a philosopher dies* of starvation.
* Every philosopher needs to eat and should never starve.

**In an easier language :**

* There is at least one thread for the program to run.
* The thread needs to be in "multiple states", as waiting, doing something, or be 'alive/dead'.
* When a thread wants to take action, it needs to take ressource that other thread can't access anymore, and after action, the thread needs to put back the ressource.
* The program should stop when a thread 'dies'.

## 📋 Table of Contents ##

* [📖 Introduction](#introduction-en)
* [🚀 Usage](#usage-en)
* [⚙️ Compilation](#compilation-en)
* [📝 Additionnal Notes](#notes-en)

## <a name="usage-en">🚀 Usage ##

```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

* **number_of_philosophers**: The number of philosophers and also the number
of forks.
* **time_to_die** (in milliseconds): If a philosopher didn’t start eating time_to_die
milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
* **time_to_eat** (in milliseconds): The time it takes for a philosopher to eat.
During that time, they will need to hold two forks.
* **time_to_sleep** (in milliseconds): The time a philosopher will spend sleeping.

[OPTIONNAL] :

* **number_of_times_each_philosopher_must_eat** : If all
philosophers have eaten at least number_of_times_each_philosopher_must_eat
times, the simulation stops. If not specified, the simulation stops when a
philosopher dies.

\[arg] is optionnal but \<arg2\> isn't.

## <a name="compilation-en">⚙️ Compilation ##

Use ``make`` for compiling the executable

```sh
make
```

## <a name="notes-en">📝 Additionnal Notes ##

It's using actual threads of the device it's running on so if you are creating more philosopher as you have threads available, it will be pretty slow.
As philosophers are waiting for all other philosophers to be ready, it's creating a huge waiting list of virtual threads to be assigned to 'physical threads'.

You should be aware of the number of threads on your computer before using this program (+ 800 to +4000 is possible but slow).

---

# Problème du Dîner des philosophes #

## <a name="introduction-fr">📖 Introduction ##

Implémentation du problème du 'Dîner des philosphes', formulé en 1965 par Edsger Dijkstra en tant qu'exercise pour un examen pour ses étudiants.
Rapidement après, Tony Hoare a repris le problème et c'est sa forme actuelle.

Voir le lien pour plus d'informations :
[📖 Dîner des philosophes](https://fr.wikipedia.org/wiki/D%C3%AEner_des_philosophes)

### Prérequis ###

* Un ou plusieurs philosophes sont assis autour d'une table ronde. Il y a un grand plat de spaghetti au milieu de celle-ci.

* Les philosophes alternent entre manger, réfléchir ou dormir. Quand ils mangent, ils ne réfléchissent ni ne dorment.
Quand ils réfléchissent, ils ne mangent ni ne dorment.
Et évidemment, lorsqu'ils dorment, ils ne font rien d'autre.
* Il y a des fourchettes au centre de la table. Il y a autant de fourchettes que de philosophes.
* Comme il n'est pas pratique de n'avoir qu'une seule fourchette, un philosophe prends une fouchette dans sa main gauche et une autre dans sa main droite pour manger.
* Quand un philosophe a fini de manger, il repose ses fourchettes sur la table et va dormir. À son réveil, il commence par réfléchir à nouveau. La simulation s'arrête lorsqu'un *philosophe meurt* de faim.
* Chaque philosophe a besoin de manger et de doit pas être affamé.

**Ou de façon plus simple :**

* Il y a au moins un un thread pour que le programme fonctionne.
* Le thread a besoin de pouvoir être dans "plusieurs états", comme attendre, faire quelque chose ou être en vie/être mort.
* Quand un thread veut faire quelque chose, il doit prendre une ressource auquels les autres threads n'auront plus accès, et ensuite doit rendre cette ressource tout seul.
* Le programme s'arrête lorsqu'un thread meurt.


## 📋 Table des matières ##

* [📖 Introduction](#introduction-fr)
* [🚀 Usage](#usage-fr)
* [⚙️ Compilation](#compilation-fr)
* [📝 Notes supplémentaires](#notes-fr)

## <a name="usage-fr">🚀 Utilisation ##


```sh
./philo <number_of_philosophers> <time_to_die> <time_to_eat> <time_to_sleep> [number_of_times_each_philosopher_must_eat]
```

* **number_of_philosophers**: Le nombre de philosophe ainsi que le nombre de fourchettes
* **time_to_die** (in milliseconds): Si un philosophe ne commence pas de manger avant le délai prévu depuis son dernier repas, il meurt.
* **time_to_eat** (in milliseconds): Le temps que met un philosophe à manger, pendant ce temps, il a besoin d'avoir deux fourchettes.
* **time_to_sleep** (in milliseconds): Le temps que met un philosophe à dormir.

[OPTIONNEL] :

* **number_of_times_each_philosopher_must_eat** : Si un philosophe a mangé au moins number_of_times_each_philosopher_must_eat fois, la simulation s'arrête. Si non spécifié, la simulation s'arrête quand un philosophe meurt.

\[arg] est optionnel mais \<arg2\> ne l'est pas.


## <a name="compilation-fr">⚙️ Compilation ##

Utiliser ``make`` pour compiler l'exécutable

```sh
make
```

Pour l'utiliser dans un programme, vous devriez ajouter `-lftprintf` à vos lignes de compilation.

## <a name="notes-fr">📝 Notes Supplémentaires ##

Le programme utilise les threads de l'appareil sur lequel il tourne donc si vous créez plus de philosophes qu'il y a de threads disponibles, le résultat sera assez lent.
Comme les philosophes attendent que tout les autres soient prêt pour démarrer, cela crée une grande liste de threads virtuels qui sont assignés aux 'threads physiques'.

Vous devriez savoir combien de threads il y a sur votre ordinateur avant d'utilier le programme (+ de 800 à + 4000 threads est possible mais lent).
