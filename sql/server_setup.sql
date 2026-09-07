CREATE TABLE answers (
    question    TEXT PRIMARY KEY,
    answer      TEXT NOT NULL 
);  

INSERT INTO answers (question, answer)
    VALUES
        ('What is the capital of Taiwan?', 'Taipei'),
        ('How many days are in a week?', 'Seven'),
        ('What is the chemical formula for water?', 'H2O');

