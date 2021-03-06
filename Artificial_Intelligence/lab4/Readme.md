# Нейронные сети: отчет по лабораторной работе студента группы М8о-406Б-18 Кузьмичева Александра


**Цель работы:** подготовить набор данных и построить несколько нейросетевых классификаторов для распознавания рукописных символов. 

Вариант 1: Символы принадлежности множеству, пересечения, объединения множеств и пустого множества.

### Исходные изображения
Для подготовки датасета от руки было написано 400 символов (по 100 символов каждого вида): [Исходные фотографии](https://github.com/poisoned-monkey/lab-neural-networks-vision-poisoned_monkey/tree/main/images)

### Полученный набор данных

Для выполнения лабораторной работы необходимо было получить размеченный датасет. Для этого изображения из предыдущего шага были разбиты на 400 изображений размером 32x32, и затем разделены на 4 категории.

[Размеченный датасет](https://github.com/poisoned-monkey/lab-neural-networks-vision-poisoned_monkey/tree/main/dataset)

### Код

Вся програмная реализация вынесена в [Notebook](https://github.com/poisoned-monkey/lab-neural-networks-vision-poisoned_monkey/blob/main/Solution.ipynb).

### Выводы

При написании этой командной лабораторной в одиночку, я на себе прочувствовал все этапы реализации data science проекта: сбор данных, подготовка данных, построение модели и её оптимизация, анализ результатов. Было интересно также проверить, насколько полносвязные нейросети уступают свёрточным при работе с изображениями. Так как свёрточные нейросети имеют меньше весов, то они быстрее обучаются. К тому же, при работе с полносвязными сетями нужны векторы, а reshape в один вектор "убивает" всю пространственную информацию об изображении. Поэтому свёрточные нейросети намного лучше подходят для классификации, детекции, сегментации и многих других задач computer vision.
