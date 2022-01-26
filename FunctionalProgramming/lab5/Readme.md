**Вариант № 5.38**
Определите обобщённую функцию SUB2, производящую вычитание двух чисел либо многочленов.  
(defgeneric sub2 (arg1 arg2)  
  ...)  

(defmethod sub2 ((p1 polynom) (p1 polynom))  
  ...)
