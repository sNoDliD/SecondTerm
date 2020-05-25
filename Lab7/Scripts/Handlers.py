from Scripts.Resources import Bot, timer
from Scripts.Classes import User
from Scripts.Registartion import registration, add_group_id, first_message, confirm_user
bot = Bot()


def action_handler(update):
    user = User(update.chat_id)

    if user.action == 'registration':
        registration(update, user)

    pass


def callback_query_handler(update, user):
    params = update.data.split('=')
    what = params[0]
    if what == 'g_id':
        if user.action == 'registration':
            add_group_id(update, user, params)

    if what == 'ans':
        type_2 = params[1]
        if type_2 == 'reg':
            confirm_user(update, user, params[2:])
    pass


def command_handler(update):
    bot.delete_message(update.chat_id, update.message_id)
    user = User(update.chat_id)
    command = update.text.split()[0][1:]

    if command == 'start':
        first_message(user)

    pass


@timer
def update_handler(update):
    user = User(update.chat_id)
    if update.edited or user.action == 'ban':
        return

    if update.data:
        callback_query_handler(update, user)

    elif user.action:
        action_handler(update)

    elif update.text.startswith('/'):
        command_handler(update)

    else:
        bot.delete_message(user.id, update.message_id)
