import sqlite3
import os

path = r'%s' % os.path.dirname(os.path.abspath(__file__)).replace('\\', '/')

databaseFile = path + '/DataBase.db'
sqlFile = path + '/db.sql'


def open_close_conn(func):
    def new_func(*args, **kwargs):
        conn = sqlite3.connect(databaseFile)

        try:
            result = func(*args, **kwargs, cursor=conn.cursor())
        except sqlite3.Error as error:
            # print("Failed into sqlite: ", error, args, kwargs)
            result = Exception
        finally:
            if conn:
                conn.commit()
                conn.close()

        return result

    return new_func


@open_close_conn
def get_query(query, unpack=False, values=None, limit=None, offset=None, cursor=None):
    if limit or offset:
        query = query[:-1] if query[-1] == ';' else query
        if type(limit) is int:
            query += f' LIMIT {limit} '
        if type(offset) is int:
            query += f' OFFSET {offset}'
        query += ';'

    cursor.execute(query) if values is None else cursor.execute(query, values)

    result = cursor.fetchall()

    if unpack and result and len(result) == 1:
        (result, ) = result
        if isinstance(result, tuple) and len(result) == 1:
            (result, ) = result

    return result


def re_create():
    if os.path.isfile(databaseFile):
        os.remove(databaseFile)

    qry = open(sqlFile, 'r').read()
    conn = sqlite3.connect(databaseFile)
    cursor = conn.cursor()
    try:
        cursor.executescript(qry)
        # cursor.execute('''insert into groups(name, teacher_id) values ('K-19', 738016227), ('K-18', 738016227);''')
        # conn.commit()
    except Exception as e:
        print('Error: ', e)
        cursor.close()


if __name__ == '__main__':
    re_create()
