import requests
import datetime
from functools import wraps
from .config import TOKEN


def debug(func):
    @wraps(func)
    def wrapper_debug(*args, **kwargs):
        args_repr = list(map(repr, args))
        kwargs_repr = list(f"{k}={v!r}" for k, v in kwargs.items())
        signature = ", ".join(args_repr + kwargs_repr)
        print(f"Вызываем {func.__name__}({signature})")
        value = func(*args, **kwargs)
        print(f"{func.__name__!r} возвращает {value!r}")
        return value
    return wrapper_debug


def timer(func):
    @wraps(func)
    def wrapper_timer(*args, **kwargs):
        start = datetime.datetime.today()
        value = func(*args, **kwargs)
        total = datetime.datetime.today() - start
        print(f"Функция {func.__name__!r} выполнена за {total.total_seconds():.4f} мс")
        return value
    return wrapper_timer


def _check_result(result):
    if result.status_code != 200:
        msg = 'The server returned HTTP {0} {1}. Response body:\n[{2}]'\
            .format(result.status_code, result.reason, result.text.encode('utf8'))
        raise Exception(msg)

    try:
        result_json = result.json()
    except:
        msg = 'The server returned an invalid JSON response. Response body:\n[{0}]'.format(result.text.encode('utf8'))
        raise Exception(msg)

    if not result_json['ok']:
        msg = 'Error code: {0} Description: {1}' \
            .format(result_json['error_code'], result_json['description'])
        raise Exception(msg)
    return result_json


class Bot:
    __instance = None

    def __new__(cls):
        if not Bot.__instance:
            print('create new instance of bot')
            instance = object.__new__(cls)
            instance.bot_url = f'https://api.telegram.org/bot{TOKEN}/'
            instance._session = None
            Bot.__instance = instance

        return Bot.__instance

    @timer
    def send_message(self, chat_id, text, markup=None):
        data = {'chat_id': chat_id, 'text': text, 'parse_mode': 'HTML'}
        if markup:
            data['reply_markup'] = markup.dumps()

        return self.__do_request(f'{self.bot_url}sendMessage', data)

    def edit_message(self, chat_id, message_id, text, markup=None):
        if not message_id:
            return self.send_message(chat_id, text, markup)

        data = {'chat_id': chat_id, 'text': text, 'message_id': message_id}
        if markup:
            data['reply_markup'] = markup.dumps()

        return self.__do_request(f'{self.bot_url}editMessageText', data)

    def delete_message(self, chat_id, message_id):
        data = {'chat_id': chat_id, 'message_id': message_id}

        return self.__do_request(f'{self.bot_url}deleteMessage', data)

    @timer
    def answer_callback_query(self, query_id, text, alert=False):
        data = {'callback_query_id': query_id, 'text': text, 'show_alert': alert}

        return self.__do_request(f'{self.bot_url}answerCallbackQuery', data)

    def get_updates(self, offset, limit=1):
        data = {'limit': limit, 'offset': offset}

        return self.__do_request(f'{self.bot_url}getUpdates', data)

    def leave_chat(self, chat_id):
        data = {'chat_id': chat_id}

        return self.__do_request(f'{self.bot_url}leaveChat', data)

    def get_chat(self, chat_id):
        data = {'chat_id': chat_id}

        return self.__do_request(f'{self.bot_url}getChat', data)

    def __do_request(self, url, param, method='post'):
        if not self._session:
            self._session = requests.session()
        return _check_result(self._session.request(method, url, param))['result']
