import tkinter as tk
from twilio.rest import Client

# Your Twilio Account SID and Auth Token
account_sid = 'AC0e5aba029071c04cde505f3f937bb2ef'
auth_token = '0f822571bf4a0fddab7b81b33b0a16ea'
client = Client(account_sid, auth_token)

# Define your question-answer pairs
qa_pairs = {
    "Do you have a fever?": False,
    "Do you have a cough?": False,
    "Do you have difficulty breathing?": False,
    "Do you have stomach pain?": False,
    "Do you have head ache?": False,
    "Have you experienced similar symptoms in the past?": False,
    "Do you smoke, drink alcohol, or use recreational drugs?": False,
    
}

# Function to handle button click event
def submit_answers():
    medications = []
    for question, _ in qa_pairs.items():
        answer = answers[question].get().lower()
        if answer == "yes":
            if question == "Do you have a fever?":
                medications.append(get_fever_medication())
                
            elif question == "Do you have a cough?":
                medications.append(get_cough_medication())
            elif question == "Do you have difficulty breathing?":
                medications.append(get_breathing_medication())
            elif question == "Do you have stomach pain?":
                medications.append(get_stomach_pain_medication())
            elif question == "Do you have head ache?":
                medications.append(get_headache_medication())
            elif question == "Have you experienced similar symptoms in the past?":
                medications.append("Consult doctor for further evaluation")
            elif question == "Do you smoke, drink alcohol, or use recreational drugs?":
                medications.append("Quit smoking and avoid alcohol or recreational drugs")
            

            
        
    if medications:
        send_sms("Prescribed medication(s): \n" + "\n".join(medications))
    else:
        send_sms("No specific medication prescribed. Consult doctor if needed.")

# Function to determine fever medication based on age
def get_fever_medication():
    age = int(age_entry.get())
    if age < 12:
        return "Children's Tylenol for fever"
    elif age >= 12 and age <= 16:
        return "Paracetemol250 for fever"
    else:
        return "Paracetemol500 for fever"

# Function to determine cough medication based on age
def get_cough_medication():
    age = int(age_entry.get())
    if age < 12:
        return "DaburHonitus for cough"
    elif age >= 12 and age < 60:
        return "Ambrolite D for cough"
    else:
        return "Reswas for cough"
    

# Function to determine breathing medication based on age
def get_breathing_medication():
    age = int(age_entry.get())
    if age < 12:
        return "Inhaler for breathing difficulty"
    else:
        return "Nasel drops for breathing difficulty"
    
# Function to determine stomach pain medication based on age
def get_stomach_pain_medication():
    age = int(age_entry.get())
    if age < 12:
        return "Children's Antacid for stomach pain"
    else:
        return "Gastracid for stomach pain" 

# Function to determine headache medication based on age
def get_headache_medication():
    return "Acetaminophen for headache"

# Function to send SMS using Twilio
def send_sms(message):
    
    from_number = '+12512921323'
    to_number = 'you need to mention'

    client.messages.create(
        to=to_number,
        from_=from_number,
        body=message
    )

# Create the main window
root = tk.Tk()
root.title("Health Assessment")

# Create labels, entries, and buttons for each question
answers = {}
row = 0
for question, _ in qa_pairs.items():
    label = tk.Label(root, text=question)
    label.grid(row=row, column=0)
    answers[question] = tk.StringVar()
    entry = tk.Entry(root, textvariable=answers[question])
    entry.grid(row=row, column=1)
    row += 1

# Ask for age
age_label = tk.Label(root, text="Enter your age:")
age_label.grid(row=row, column=0)
age_entry = tk.Entry(root)
age_entry.grid(row=row, column=1)
row += 1

# Ask for weight
weight_label = tk.Label(root, text="Enter your weight (kg):")
weight_label.grid(row=row, column=0)
weight_entry = tk.Entry(root)
weight_entry.grid(row=row, column=1)
row += 1

button = tk.Button(root, text="Submit", command=submit_answers)
button.grid(row=row, columnspan=2)

root.mainloop()
