from Scripts.Resources import Bot
from Scripts.Classes import Update
from Scripts.Handlers import update_handler

last_update_id = None
bot = Bot()


def main():
    global last_update_id

    while True:
        update = bot.get_updates(last_update_id)
        if update:
            # print(update)
            update = Update(**update[0])
            last_update_id = update.id + 1

            update_handler(update) if update.chat_id > 0 else bot.leave_chat(update.chat_id)


if __name__ == '__main__':
    main()










