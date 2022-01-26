(defun make-term(&key order coeff)
    (list order coeff))

(defun order(term) (first term))
(defun coeff(term) (second term))

(defclass polynom ()
 ((var-symbol :initarg :var :reader var)
  
  (term-list :initarg :terms :reader terms)))

(defgeneric zerop1 (arg)
 (:method ((n number))   ; (= n 0)
  (zerop n)))

(defgeneric minusp1 (arg)
 (:method ((n number))   ; (< n 0)
  (minusp n)))

(defmethod print-object ((p polynom) stream)
  (format stream "[�� (~s) ~:{~:[~:[+~;-~]~d~[~2*~;~s~*~:;~s^~d~]~;~]~}]"
          (var p)
          (mapcar (lambda (term)
                    (list (zerop1 (coeff term))
                          (minusp1 (coeff term))
                          (if (minusp1 (coeff term))
                              (abs (coeff term))
                              (coeff term))
                          (order term)
                          (var p)
                          (order term)))
                  (terms p))))

(defgeneric sub2 (arg1 arg2))

(defmethod sub2((arg1 polynom) (arg2 polynom))
  (let ((index1 0)(index2 0)(cur-term NIL))
    (if (not (equal (var arg1) (var arg2)))
        NIL
        (make-instance 'polynom :var (var arg1) :terms (loop while (or (< index1 (length (terms arg1))) (< index2 (length (terms arg2))))
          do
          (setf cur-term 
            (cond ((and (< index1 (length (terms arg1))) (< index2 (length (terms arg2)))) 
                    (let((term1 (nth index1 (terms arg1)))(term2 (nth index2 (terms arg2))))
                      (cond ((= (order term1) (order term2)) (setf index1 (+ 1 index1)) (setf index2 (+ 1 index2)) (make-term :order (order term1) :coeff (- (coeff term1) (coeff term2))))
                            ((< (order term1) (order term2)) (setf index2 (+ 1 index2)) (make-term :order (order term2) :coeff (- (coeff term2))))
                            ((> (order term1) (order term2)) (setf index1 (+ 1 index1)) term1)
                      )
                    ))
                  ((< index1 (length (terms arg1))) (setf index1 (+ 1 index1)) (nth (- index1 1) (terms arg1)))
                  (else (setf index2 (+ 1 index2)) (make-term :order (order (nth (- index2 1) (terms arg2))) :coeff (- (coeff (nth (-index2 1) (terms arg2))))))
            )
          )
          if (/= 0 (coeff cur-term)) collect cur-term
        ))
    )
  )
)

(sub2 (make-instance 'polynom :var 'x :terms '((5 2) (3 2) (1 4) (0 5)))
      (make-instance 'polynom :var 'x :terms '((5 2) (4 1) (2 2) (1 3))))