import pandas as pd
import matplotlib.pyplot as plt
import os

# Fonction pour trouver le dernier dossier créé
def get_latest_test_directory(base_dir="Test_results"):
    test_dirs = [d for d in os.listdir('.') if d.startswith(base_dir) and os.path.isdir(d)]
    test_dirs.sort(key=lambda x: int(x.split('_')[-1]))
    return test_dirs[-1] if test_dirs else None

# Trouver le dernier dossier de test
test_dir = get_latest_test_directory()
if not test_dir:
    print("Aucun dossier de test trouvé.")
    exit(1)

# Chemin complet vers le fichier CSV
csv_path = os.path.join(test_dir, 'sort_results.csv')
if not os.path.exists(csv_path):
    print(f"Le fichier {csv_path} n'existe pas.")
    exit(1)

# Charger les données à partir du fichier CSV
df = pd.read_csv(csv_path)

# Afficher les premières lignes du dataframe pour vérifier le chargement des données
print(df.head())

# Afficher des statistiques descriptives
print("\nStatistiques descriptives :")
stats = df.describe()

# Corriger le formatage pour les valeurs qui doivent être des entiers
for col in stats.columns:
    if stats[col].dtype == 'float64':
        stats[col] = stats[col].apply(lambda x: int(x) if x.is_integer() else x)

print(stats)

# Visualiser les données

# Temps d'exécution
plt.figure(figsize=(10, 6))
plt.bar(df['Algorithm'], df['Time Spent (s)'], color='skyblue')
plt.xlabel('Algorithm')
plt.ylabel('Time Spent (s)')
plt.title('Time Spent by Sorting Algorithms')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig(os.path.join(test_dir, 'time_spent.png'))
# plt.show()  # Commented out to avoid interactive display issues

# Utilisation de la RAM
plt.figure(figsize=(10, 6))
plt.bar(df['Algorithm'], df['RAM Usage (KB)'], color='lightgreen')
plt.xlabel('Algorithm')
plt.ylabel('RAM Usage (KB)')
plt.title('RAM Usage by Sorting Algorithms')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig(os.path.join(test_dir, 'ram_usage.png'))
# plt.show()  # Commented out to avoid interactive display issues

# Temps CPU utilisateur
plt.figure(figsize=(10, 6))
plt.bar(df['Algorithm'], df['User CPU (s)'], color='salmon')
plt.xlabel('Algorithm')
plt.ylabel('User CPU (s)')
plt.title('User CPU Time by Sorting Algorithms')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig(os.path.join(test_dir, 'user_cpu_time.png'))
# plt.show()  # Commented out to avoid interactive display issues

# Temps CPU système
plt.figure(figsize=(10, 6))
plt.bar(df['Algorithm'], df['Sys CPU (s)'], color='orange')
plt.xlabel('Algorithm')
plt.ylabel('Sys CPU (s)')
plt.title('System CPU Time by Sorting Algorithms')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig(os.path.join(test_dir, 'sys_cpu_time.png'))
# plt.show()  # Commented out to avoid interactive display issues

# Changements de contexte involontaires
plt.figure(figsize=(10, 6))
plt.bar(df['Algorithm'], df['Invol CS'], color='purple')
plt.xlabel('Algorithm')
plt.ylabel('Involuntary Context Switches')
plt.title('Involuntary Context Switches by Sorting Algorithms')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig(os.path.join(test_dir, 'invol_cs.png'))
# plt.show()  # Commented out to avoid interactive display issues

# Changements de contexte volontaires
plt.figure(figsize=(10, 6))
plt.bar(df['Algorithm'], df['Vol CS'], color='pink')
plt.xlabel('Algorithm')
plt.ylabel('Voluntary Context Switches')
plt.title('Voluntary Context Switches by Sorting Algorithms')
plt.xticks(rotation=45)
plt.tight_layout()
plt.savefig(os.path.join(test_dir, 'vol_cs.png'))
# plt.show()  # Commented out to avoid interactive display issues

# Comparaison des différentes métriques
metrics = ['Time Spent (s)', 'RAM Usage (KB)', 'User CPU (s)', 'Sys CPU (s)', 'Invol CS', 'Vol CS']

for metric in metrics:
    plt.figure(figsize=(10, 6))
    plt.plot(df['Algorithm'], df[metric], marker='o')
    plt.xlabel('Algorithm')
    plt.ylabel(metric)
    plt.title(f'{metric} by Sorting Algorithms')
    plt.xticks(rotation=45)
    plt.tight_layout()
    plt.savefig(os.path.join(test_dir, f'{metric.lower().replace(" ", "_")}.png'))
    # plt.show()  # Commented out to avoid interactive display issues
