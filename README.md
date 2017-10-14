# RotationLogger

Одноплатный компьютер (контроллер) имеет небольшой объем дискового пространства. Необходимо написать класс Logger, который позволяет хранить наиболее актуальную информацию о работе контроллера, избавляясь от старой (по кругу). 

Информация пишется в несколько лог файлов ограниченного размера и передается на сервер в случайные моменты (когда устанавливается качественная связь), переданные файлы на контроллере стираются. Дозапись всегда ведется в последний лог-файл, если размер позволяет. Если на контроллере накапливается максимальное количество лог-файлов не переданных на сервер, самый старый пересоздается. 

Приложение, которое использует логгер, не многопоточное, но может быть запущено одновременно в нескольких экземплярах (запускается, выполняет свою работу и закрывается). 

Имена файлов должны быть уникальны, чтобы лог-файлы на сервере не перезатирались.

     Тестовое задание успешно выполнено и одобрено
     
     
