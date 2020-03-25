
ProjectHome = File.expand_path(File.dirname(__FILE__))
ProjectName = "smart_home"
SrcDir = "#{ProjectHome}/src"
BuildDir = "#{ProjectHome}/build"
ExeFileDir = "#{BuildDir}/exe"
ObjFilesDir = "#{BuildDir}/objects"
ExeFilePath = "#{ExeFileDir}/#{ProjectName}.exe"
IncludeDirs = %w(/usr/local/boost_1_72_0/)

Cxx = 'clang++'
Flags = '-Wall -O0 -DNDEBUG -std=c++2a -I/opt/vc/include -L/opt/vc/lib -lbcm_host'

task :default => ['build']

def get_match_files_recursion(path, &block)

  files = []

  Dir.each_child(path) do |f|

    file = "#{path}/#{f}"

    case File.ftype(file).to_sym
    when :directory
      files.concat(get_match_files_recursion(file, &block))
    when :file
      files << file if yield(file)
    else
    end
  end

  return files
end

desc "build exe file to all"
task :build do |task, args|
  Rake::Task['build:clean'].execute
  Rake::Task['build:compile'].execute(args)
  Rake::Task['build:link'].execute
end

namespace :build do

  desc "build obj file"
  task :compile do |task, args|

    FileUtils.mkdir_p(ObjFilesDir) unless Dir.exists?(ObjFilesDir)

    func = ->(f){ File.fnmatch("*.cpp", f) }
    if args['all'].nil? || !!!args['all']
      #todo timestamp で差分のみ
    end

    cpp_files = get_match_files_recursion(SrcDir, &func)

    cpp_files.each do |f|
      target = File.basename(f, '.cpp')
      sh "#{Cxx} #{Flags} -idirafter #{IncludeDirs.join(' ')} -o #{ObjFilesDir}/#{target}.o -c #{f}"
    end
  end

  desc "build exe file"
  task :link do
    FileUtils.mkdir_p(ExeFileDir) unless Dir.exists?(ExeFileDir)
    obj_files = get_match_files_recursion(ObjFilesDir){|f| File.fnmatch("*.o", f)}.join(' ')
    sh "#{Cxx} #{Flags} -o #{ExeFilePath} #{obj_files}"
  end

  desc "rm build dir"
  task :clean do
    sh "rm -r #{BuildDir}" if Dir.exists?(BuildDir)
  end
end
