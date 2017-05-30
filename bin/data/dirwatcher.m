dir_content = dir;
filenames = {dir_content.name};
current_files = filenames;
while true
  dir_content = dir;
  filenames = {dir_content.name};
  new_files = setdiff(filenames,current_files);
  if ~isempty(new_files)
    % deal with the new files
     fprintf('new file found\n ')
    current_files = filenames;
    new_files
   
    
  else
   % fprintf('no new files\n')
  end
end