CREATE TABLE IF NOT EXISTS groups (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 name VARCHAR UNIQUE NOT NULL,
                 teacher_id INTEGER NOT NULL,
                 headman_id INTEGER);

CREATE TABLE IF NOT EXISTS labs (
                 id INTEGER PRIMARY KEY AUTOINCREMENT,
                 group_id INTEGER NOT NULL,
                 name VARCHAR NOT NULL,
                 params TEXT);

CREATE TABLE IF NOT EXISTS users (
                 id INTEGER PRIMARY KEY,
                 group_id INTEGER ,
                 name VARCHAR UNIQUE,
                 status INTEGER,
                 last_markup INTEGER,
                 action TEXT);

CREATE TABLE IF NOT EXISTS choice (
                 lab_id INTEGER NOT NULL,
                 user_id INTEGER NOT NULL,
                 variant VARCHAR);

CREATE TRIGGER IF NOT EXISTS delete_lab
                        BEFORE DELETE ON labs
                        BEGIN
                            DELETE FROM choice WHERE lab_id LIKE OLD.id;
                        END;

CREATE TRIGGER IF NOT EXISTS delete_student
                        BEFORE DELETE ON users
                        BEGIN
                            DELETE FROM choice WHERE user_id LIKE OLD.id;
                            -- todo: delete group teacher?
                        END;

CREATE TRIGGER IF NOT EXISTS delete_group
                        BEFORE DELETE ON groups
                        BEGIN

                            DELETE FROM labs WHERE group_id = OLD.id;

                            UPDATE users
                                SET group_id = NULL
                                WHERE group_id = OLD.id;

                        END;

-- todo: also update group = None, WHERE status = 0
CREATE TRIGGER IF NOT EXISTS update_student
                        AFTER UPDATE ON users
                        BEGIN
                            --DELETE FROM choice WHERE user_id = NEW.id
                            --    AND (OLD.group_id <> NEW.group_id OR NEW.status = 0);
                            DELETE FROM choice WHERE user_id = NEW.id
                                AND NEW.status = 0;
                        END;