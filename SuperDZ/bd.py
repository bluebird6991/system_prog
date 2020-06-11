from sqlalchemy import create_engine
from sqlalchemy.orm import scoped_session, sessionmaker
from sqlalchemy.sql import select
import os

from database import Base, Users

engine = create_engine(f'sqlite:///users.db')

if not os.path.isfile(f'./users.db'):
    Base.metadata.create_all(engine)

session_factory = sessionmaker(bind=engine)
Session = scoped_session(session_factory)

session = Session()



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
	count = session.query(Users).count()
	return count
# test = Users(user_id = 341115219, firstname = "Timur", role = "user")
# session.add(test)
# session.commit()

# session.query(Users).filter(Users.firstname == "Диана").delete()
# session.commit()

for instance in session.query(Users).order_by(Users.id): 
    print (instance.id, instance.user_id, instance.firstname, instance.role)

print(get_count_users())

# print(session.query(Users.user_id))
for i in session.query(Users.firstname, Users.user_id):
	print(i)
# print(check_user(139050906))
# print(check_user(1390509060))
# print(check_role(139050906, "admin"))
# print(check_role(341115219, "admin"))
	
