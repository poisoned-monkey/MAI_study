
(defun get-diag(n diag-num)
    (let ((diag-len (if (> diag-num n) (- (* 2 n) diag-num) diag-num))
          (diag-start (if (> diag-num n) (list (- diag-num n ) (- n 1)) (list 0 (- diag-num 1))))
          (result-list NIL))
          (loop for i upfrom 0 to (- diag-len 1)
            do 
            (setq result-list (cons (list (+ (first diag-start) i) (- (second diag-start) i)) result-list))

          )      
          result-list
    )
)

(defun fill-diag(matrix diag cur)
    (cond 
        (diag  
        (setf (aref matrix (first (first diag)) (second (first diag))) cur)
        (fill-diag matrix (rest diag) (+ cur 1)))))


(defun diag-matrix(n)
    (let ((matrix (make-array (list n n)))
          (diag-count (- (* 2 n) 1))
          (reverse? nil)
          (current-value 1)
          )
    
    (loop for i upfrom 1 to diag-count
        do
        (setq cur-diag (if reverse? (get-diag n i) (reverse (get-diag n i))))
        (setq reverse? (not reverse?))
        (fill-diag matrix cur-diag current-value)
        (setq current-value (+ current-value (length cur-diag)))
    )
    matrix)
)



(diag-matrix 3)
(diag-matrix 4)
(diag-matrix 5)
