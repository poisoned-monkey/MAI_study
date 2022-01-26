(defun count-real(num tree)
    (if tree
        (if (listp (first tree))
            (+ (count-real num (first tree)) (count-real num (rest tree)))
            (if (= num (first tree))
                (+ 1 (count-real num (rest tree)))
                (count-real num (rest tree))
            )
        )
        0
    )
)