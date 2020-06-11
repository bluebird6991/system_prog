#import aiogram
#from aiogram import Bot, types
from aiogram.dispatcher import Dispatcher
from aiogram.utils import executor
from aiogram import Bot
from aiogram import types
from aiogram.utils.markdown import text, bold, italic, code, pre
from aiogram.types import ParseMode, InputMediaPhoto, InputMediaVideo, ChatActions
from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from sqlalchemy.sql import select
import os
import re

from database import Base, Users
import keyboards as kb
from config import TOKEN

engine = create_engine(f'sqlite:///users.db')

if not os.path.isfile(f'./home/pi/ArturBot/bot3/users.db'):
    Base.metadata.create_all(engine)

session_factory = sessionmaker(bind=engine)
Session = scoped_session(session_factory)

session = Session()
# test = Users(user_id = 139050906, firstname = "Andrey", role = "admin")
# session.add(test)
# session.commit()


# for instance in session.query(Users).order_by(Users.id): 
#     print (instance.id, instance.user_id, instance.firstname, instance.role)


def check_user(id):
	count = session.query(Users.user_id).filter(Users.user_id == id).count()
	if count == 1:
		return True
	elif count == 0:
		return False
	else:
		print("Error")


def check_role(id, role):
	role = session.query(Users).filter(Users.role == role, Users.user_id == id).count()
	if role == 1:
		return True
	elif role == 0:
		return False
	else:
		print("Error")

def get_admins_id():
	admins = session.query(Users).filter(Users.role == "admin")
	for i in admins:
		return(i.user_id)
	return False

def get_count_users():
	return session.query(Users).count()

def add_ssh_pub_to_tmp(key):
	f = open("/home/pi/ArturBot/bot3/ssh.tmp", "w+")
	f.write(key)
	f.close

def check_add_ssh_pub():
	return os.popen("/home/pi/ArturBot/bot3/check_add_ssh_pub.sh").read()

def get_temp():
	return os.popen("sudo /home/pi/ArturBot/bot3/temp").read()

bot = Bot(token = TOKEN)
dp = Dispatcher(bot)

@dp.message_handler(commands=['start'])
async def process_start_command(message):
	if check_user(message.from_user.id):
		if check_role(message.from_user.id, "admin"):
			await bot.send_message(message.from_user.id, "Hello admin")
		elif check_role(message.from_user.id, "user"):
			await bot.send_message(message.from_user.id, "Hello user")
	else:
		await bot.send_message(message.from_user.id, "Вы не авторизованы.\nВаш запрос отправлен администратору!!!")
		await bot.send_message(get_admins_id(), text = u'Добавить пользователя "%s" (id:%d)?' % (message.from_user.first_name, message.from_user.id), reply_markup=kb.add_new_user(message.from_user.id, message.from_user.first_name))

@dp.message_handler(commands=['help'])
async def process_help_command(message: types.Message):
	msg = text(bold('Я могу ответить на следующие команды:'),
		'/start', '/help', '/ssh_add', '/check_temp', '/list', '/del_user', sep='\n')
	await bot.send_message(message.from_user.id, msg)


@dp.message_handler(commands=['ssh_add'])
async def process_ssh_add_command(message: types.Message):
	if check_user(message.from_user.id):
		await bot.send_message(message.from_user.id, text = u'Скопируйте ваш публичный ключ, затем вставьте сюда и поставьте вначале "/"')
	else:
		await bot.send_message(message.from_user.id, text = u'Вы не авторизованы!!!')


@dp.message_handler(commands=['ssh-rsa'])
async def process_ssh_rsa_command(message: types.Message):
	if check_user(message.from_user.id):
		key = re.split(r'\s{1,}', message.text)
		if len(key) == 3:
			await bot.send_message(get_admins_id(), text = u'Пользователь %s (id:%s) хочет добавить свой публичный ssh ключ!!!' % (message.from_user.first_name, message.from_user.id), reply_markup = kb.add_ssh(message.from_user.id, message.from_user.first_name))
			string = key[0]
			for i in range(1, 3):
				string = u'%s %s' % (string, key[i])
			string = u'%s\n' % (string[1:])
			#print(string)
			add_ssh_pub_to_tmp(string)
	else:
		await bot.send_message(message.from_user.id, text = u'Вы не авторизованы!!!')


@dp.message_handler(commands=['check_temp'])
async def process_ssh_rsa_command(message: types.Message):
	if check_user(message.from_user.id):
		await bot.send_message(message.from_user.id, get_temp())
	else:
		await bot.send_message(message.from_user.id, text = u'Вы не авторизованы!!!')

@dp.message_handler(commands=['list'])
async def process_list_command(message: types.Message):
    if check_role(message.from_user.id, "admin"):
    	string = ""
    	for instance in session.query(Users).order_by(Users.id): 
		    string = "%s%d.\t%s\t(id:%d)\n" % (string, instance.id, instance.firstname, instance.user_id)
    	await bot.send_message(message.from_user.id, text = string)
    else:
    	await bot.send_message(message.from_user.id, text = u'Вы не root!!!')

@dp.message_handler(commands=['del_user'])
async def process_help_command(message: types.Message):
	if check_role(message.from_user.id, "admin"):
		if not get_count_users() == 0:
			await bot.send_message(message.from_user.id, text = u'Вы в root!!!')
			await bot.send_message(message.from_user.id, text = u'Выберите пользователя котогрого хотите удалить!!!', reply_markup = kb.generate_buttons(session.query(Users.firstname, Users.user_id)))
		else:
			await bot.send_message(message.from_user.id, text = u'Список пользователей пуст!!!')
	else:
		await bot.send_message(message.from_user.id, text = u'Пшел отсюда!!!')

@dp.message_handler()
async def process_digt_command(message: types.Message):
	if check_user(message.from_user.id):
		if message.text.isdigit():
			global time
			time = int(message.text)
			await bot.send_message(message.from_user.id, text = u'Выберите измерение времени!', reply_markup=kb.time_format)
		else:
			await bot.send_message(message.from_user.id, text = u'Повторите ввод')
	else:
		await bot.send_message(message.from_user.id, text = u'Вы не авторизованы.')


@dp.callback_query_handler(lambda call: True)
async def process_callback_button(callback_query: types.CallbackQuery):
	if callback_query.data.split(' ')[0] == 'add_approve':
		if not check_user(int(callback_query.data.split(' ')[1])):
			user = Users(user_id = callback_query.data.split(' ')[1], firstname = callback_query.data.split(' ')[2], role = "user")
			session.add(user)
			session.commit()
			await bot.send_message(callback_query.data.split(' ')[1], u'Доступ предоставлен!!!')
			await bot.send_message(callback_query.data.split(' ')[1], u'Нажмите /help')
			await bot.send_message(callback_query.from_user.id, u'Доступ предоставлен пользователю %s (id:%s)!!!' % (str(callback_query.data.split(' ')[1]), callback_query.data.split(' ')[2]))
		else:
			await bot.send_message(callback_query.from_user.id, "Пользователь уже добавлен")
	elif callback_query.data.split(' ')[0] == 'add_decline':
		await bot.send_message(callback_query.data.split(' ')[1], u'Отказано в доступе!!!')

	elif callback_query.data.split(' ')[0] == 'ssh_approve':
			if check_add_ssh_pub() == 'True\n':
				await bot.send_message(get_admins_id(), u'SSH ключ пользователя %s (id:%s) добавлен' % (callback_query.data.split(' ')[2], callback_query.data.split(' ')[1]))
				await bot.send_message(callback_query.data.split(' ')[1], u'Ваш ключ добавлен и Вам предоставлен доступ')
			else:
				await bot.send_message(get_admins_id(), u'Ключ не верный')
				await bot.send_message(callback_query.data.split(' ')[1], u'Ключ не верный')
	elif callback_query.data.split(' ')[0] == 'ssh_decline':
		await bot.send_message(get_admins_id(), u'Пользователю %s (id:%s) отказано в добавлении SSH Ключа' % (callback_query.data.split(' ')[2], callback_query.data.split(' ')[1]))
		await bot.send_message(callback_query.data.split(' ')[1], u'Вам отказано в добавлении SSH Ключа')

	elif callback_query.data.split(' ')[0] == 'del':
			id_del = callback_query.data.split(' ')[1]
			user_del = callback_query.data.split(' ')[2]
			#ua.del_user(id_del)
			session.query(Users).filter(Users.firstname == user_del).delete()
			session.commit()
			await bot.send_message(get_admins_id(), u'Пользователь %s (id:%s) - УДАЛЕН' % (user_del, id_del))
			await bot.send_message(id_del, u'Пользователь %s (id:%s) - УДАЛЕН' % (user_del, id_del))


if __name__ == '__main__':
	executor.start_polling(dp)