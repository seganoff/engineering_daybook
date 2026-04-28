require "rbnacl"
require "json"
require "securerandom"

include RbNaCl

password = "mysecretpassword"
input_file = "plain.txt"
output_file = "encrypted.json"

#data = File.binread(input_file)

# ---- salt ----
salt = SecureRandom.random_bytes(16)
#16(recommendation)-32

# ---- Argon2id KDF ----
# rbnacl exposes argon2id via low-level API
#ops = RbNaCl::PasswordHash::Argon2::OPSLIMIT_MODERATE
#mem = RbNaCl::PasswordHash::Argon2::MEMLIMIT_MODERATE

#binding.irb;

#key = PasswordHash::Argon2::digest(
#key = RbNaCl::PasswordHash.argon2id(
#  "seguroFromStream",
#  salt,
#  ops, #3..10
#  mem,#in bytes
#64 );

passwd='seguroFromStream';ops=5;mem=32768;#2**15
argon = RbNaCl::PasswordHash::Argon2.new(ops, mem, 32);
kdf = argon.digest(passwd, salt, :argon2id);
saltu = salt.unpack1("H*");
for_bash_str = "echo -n '#{passwd}' | argon2 #{saltu} -id -t 5 -m 15 -l 32 ";
verify_bash = system(for_bash_str);
#$algorithm$version$parameters$salt(base64)$hash(base64)
#$argon2id$v=19$m=32768,t=5,p=1$<salt_b64>$<hash_b64>
binding.irb

# ---- encryption ----
box = SecretBox.new(key)

nonce = box.generate_nonce
ciphertext = box.encrypt(nonce, data)

# ---- store payload ----
payload = {
  salt: salt.unpack1("H*"),
  nonce: nonce.unpack1("H*"),
  ciphertext: ciphertext.unpack1("H*")
}

File.write(output_file, JSON.pretty_generate(payload))

puts "Encrypted → #{output_file}"
