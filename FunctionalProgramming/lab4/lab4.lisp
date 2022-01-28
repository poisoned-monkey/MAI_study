(defun russian-upper-case-p (char)
  (position char "АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"))


(defun russian-char-downcase (char)
  (let ((i (russian-upper-case-p char)))
    (if i 
        (char "абвгдеёжзийклмнопрстуфхцчшщъыьэюя" i)
        (char-downcase char))))


(defun russian-string-downcase (string)
  (map 'string #'russian-char-downcase string))


(defun parsing_str (word str)
  (let ((ind (search word str)))
  	(progn
  		(if ind
  			(
  				cond
  				((= (length str) (+ ind (length word))) ind)
  				((string= (char str (+ ind (length word))) #\Space) ind)
  				((string= (char str (+ ind (length word))) #\Tab) ind)
  				((string= (char str (+ ind (length word))) #\Newline) ind)
          ((string= (char str (+ ind (length word))) ",") ind)
          ((string= (char str (+ ind (length word))) ":") ind)
          ((string= (char str (+ ind (length word))) ";") ind)
          ((string= (char str (+ ind (length word))) "-") ind)
          ((string= (char str (+ ind (length word))) "(") ind)
  				(t (+ ind (length word)))
  			)
  			nil
    	)
    )
  )
)


(defun double_find (word index sentence)
  (if index 
  	(let 
  		((substr (subseq sentence index) ) (prev_index -1) (is-null (lambda (obj)(if (not obj) (return-from double_find nil)))))
  		(progn
  			(loop while (and (and (/= prev_index index) prev_index) (> (length substr) (length word)))
        	do (progn
    		        (setq prev_index (parsing_str word substr))
                (funcall is-null prev_index)
                (setq substr (subseq substr prev_index))
                (setq prev_index (+ index prev_index))
        	   )
			  )
			  (if index (return-from double_find index) nil)
  		)
  	)
  	nil
  )
)

(defun finding-the-word (word text)
  (if (and (/= (length word) 0) word)
      (let ((word_index nil) (sentences_amount -1) (not-null (lambda (obj)(not (null obj)))))
        (progn
          (loop for sentence in text
                until (funcall not-null word_index)
                do (progn
                     (incf sentences_amount)
                     (setf word_index (parsing_str (russian-string-downcase word) (string-right-trim ",.;:?!" (russian-string-downcase sentence))))
                     (setf word_index (double_find (russian-string-downcase word) word_index (string-right-trim ",.;:?!" (russian-string-downcase sentence))))
                    )
          )
          (if (funcall not-null word_index) (list word_index sentences_amount) nil)
        )
      )
      nil
  )
)


(defun find-the-word (word text)
  (if (finding-the-word word text) (values (car (finding-the-word word text)) (cadr (finding-the-word word text))) nil))
