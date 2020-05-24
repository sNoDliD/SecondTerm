import json

from DataBase.DataBaseWork import get_query
_temp_users = {}


class User:
    global _temp_users

    def __new__(cls, user_id):
        user_id = int(user_id)

        if user_id not in _temp_users:
            data = get_query(f'''SELECT group_id, name, status, last_markup, action 
                                    FROM users WHERE id = ?;''', values=(user_id, ), unpack=True)
            instance = super().__new__(cls)
            instance.id = user_id
            if not data:
                instance.group_id = None
                instance.name = None
                instance.status = None
                instance.last_markup = None
                instance.action = 'registration'

                get_query(f'INSERT INTO users(id, action) VALUES (?, ?)', values=(user_id, 'registration'))
            else:
                group_id, name, status, last_markup, action = data
                instance.group_id = group_id
                instance.name = name
                instance.status = status
                instance.last_markup = last_markup
                instance.action = action

            _temp_users[user_id] = instance
        else:
            instance = _temp_users[user_id]

        # todo clear if _temp_users > 100
        return instance

    def update(self):
        data = self.group_id, self.name, self.status, self.last_markup, self.action, self.id
        get_query(f'''UPDATE users SET group_id = ?, name = ?, status = ?,
                                       last_markup = ?, action = ?
                      WHERE id = ?;''', values=data)


class Update:
    def __init__(self, **kwargs):
        self.id = kwargs['update_id']
        self.edited = 'edited_message' in kwargs
        query_id, data, phone_number = None, None, None

        if 'message' in kwargs:
            kwargs = kwargs['message']

        elif 'edited_message' in kwargs:
            kwargs = kwargs['edited_message']

        elif 'callback_query' in kwargs:
            kwargs = kwargs['callback_query']
            query_id = kwargs['id']
            data = kwargs['data']
            kwargs = kwargs['message']

        self.query_id = query_id
        self.data = data
        self.message_id = kwargs.setdefault('message_id', None)
        self.chat_id = kwargs['chat'].setdefault('id', None)
        self.text = kwargs.setdefault('text', '')

        if 'entities' in kwargs:
            for entities in kwargs['entities']:
                if entities['type'] == 'phone_number':
                    phone_number = self.text[entities['offset']: entities['offset'] + entities['length']]
                    break
        self.phone_number = phone_number


def button(text, data):
    return {'text': text, 'callback_data': data}


class Markup:
    def __init__(self, buttons_list=None, row_count=1):
        if buttons_list is None or not isinstance(buttons_list, list):
            buttons_list = []

        self.row_count = row_count
        self.buttons = [[]]
        self.add(buttons_list)

    def add(self, buttons_list):
        over_size = self.row_count - len(self.buttons[-1])

        if over_size > 0:
            self.buttons[-1].extend(buttons_list[:over_size])
        button_len = len(buttons_list)

        while over_size < button_len:
            self.buttons.append(buttons_list[over_size:over_size + self.row_count])
            over_size += self.row_count

    def row(self, buttons_row):
        self.buttons.append(buttons_row)
        self.buttons.append([])

    def dumps(self):
        while [] in self.buttons:
            self.buttons.remove([])

        return json.dumps({'inline_keyboard': self.buttons})

