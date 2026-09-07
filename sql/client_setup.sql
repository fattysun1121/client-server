CREATE TABLE questions (
    id          INTEGER GENERATED ALWAYS AS IDENTITY PRIMARY KEY,
    question    TEXT NOT NULL
);

INSERT INTO questions (question)
    VALUES
        ('What is the capital of Taiwan?'),
        ('How many days are in a week?'),
        ('What is the chemical formula for water?');

