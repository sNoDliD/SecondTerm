from Scripts.Resources import Bot
from Scripts.Classes import User, Markup, button

bot = Bot()


def callback_query_handler(update):
    method = update.data.split('_')[0]

    caller = {'language': change_language,
              'time': set_experience,
              'position': change_position,
              'confirm': confirm,
              'edit': edit}

    if method in caller:
        caller[method](update)


def send_language(user):
    markup = Markup([button('RU', 'language_ru'), button('EN', 'language_en')], 2)
    send_text = {RU: 'Выберите ваш язык 🗣',
                 EN: 'Please, choose your language 🗣'}
    bot.send_message(user.id, send_text[user.language], markup)


def command_handler(update):
    bot.delete_message(update.chat_id, update.message_id)
    user = User(update.chat_id)
    command = update.text.split()[0][1:]

    if command == 'start':
        if not user.name:
            send_language(user)

        elif not user.phone:
            send_phone(user)
            user.state = Saver(set_phone)
        elif not user.city:
            send_city(user)
            user.state = Saver(set_city)
        elif not user.experience:
            send_experience(user, False)
        else:
            update.data = 'F'
            update.message_id = None
            confirm(update)

    elif command == 'language':
        send_language(user)


def update_handler(update):
    if update.edited:
        return

    user = User(update.chat_id)

    if update.data:
        callback_query_handler(update)

    elif user.action:
        pass

    elif update.text.startswith('/'):
        command_handler(update)

    elif update.text:
        if not user.name:
            send_language(user)
