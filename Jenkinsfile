pipeline {
    agent {
        docker { image 'ruby:2.7' }
    }
    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        stage('Install deps') {
            steps {
                sh 'gem install bundler'
                sh 'bundle install'
            }
        }
        stage('Codecheck') {
            steps {
                sh 'bundle exec rake rubocop'
            }
        }
        stage('Test') {
            steps {
                sh 'bundle exec rake spec'
            }
        }
        stage('Build gem') {
            steps {
                sh 'echo build'
            }
        }
        stage('Deploy to gemcutter') {
            steps {
                sh 'echo deploy'
            }
        }
    }
}
